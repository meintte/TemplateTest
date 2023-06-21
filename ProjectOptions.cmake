include(cmake/SystemLink.cmake)
include(cmake/LibFuzzer.cmake)
include(CMakeDependentOption)
include(CheckCXXCompilerFlag)

macro(TemplateTest_supports_sanitizers)
  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND NOT WIN32)
    set(SUPPORTS_UBSAN ON)
  else()
    set(SUPPORTS_UBSAN OFF)
  endif()

  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND WIN32)
    set(SUPPORTS_ASAN OFF)
  else()
    set(SUPPORTS_ASAN ON)
  endif()
endmacro()

macro(TemplateTest_setup_options)
  option(TemplateTest_ENABLE_DEVELOPER_MODE "Enable developer mode" ON)

  option(TemplateTest_ENABLE_HARDENING "Enable hardening" ON)
  cmake_dependent_option(
    TemplateTest_ENABLE_GLOBAL_HARDENING
    "Attempt to push hardening options to built dependencies"
    ON
    TemplateTest_ENABLE_HARDENING
    OFF)

  # Regardless of developer mode
  option(TemplateTest_ENABLE_COVERAGE "Enable coverage reporting" OFF)
  option(TemplateTest_ENABLE_PCH "Enable precompiled headers" OFF)
  option(TemplateTest_ENABLE_USER_LINKER "Enable user-selected linker" OFF)
  option(TemplateTest_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
  if(NOT PROJECT_IS_TOP_LEVEL)
    mark_as_advanced(
      TemplateTest_ENABLE_COVERAGE
      TemplateTest_ENABLE_PCH
      TemplateTest_ENABLE_USER_LINKER
      TemplateTest_ENABLE_UNITY_BUILD)
  endif()

  # General options
  if(NOT PROJECT_IS_TOP_LEVEL
     OR NOT TemplateTest_ENABLE_DEVELOPER_MODE
     OR TemplateTest_PACKAGING_MAINTAINER_MODE)
    option(TemplateTest_ENABLE_IPO "Enable IPO/LTO" OFF)
    option(TemplateTest_WARNINGS_AS_ERRORS "Treat Warnings As Errors" OFF)
    option(TemplateTest_ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)
    option(TemplateTest_ENABLE_CPPCHECK "Enable cpp-check analysis" OFF)
    option(TemplateTest_ENABLE_CACHE "Enable ccache" OFF)
  else()
    option(TemplateTest_ENABLE_IPO "Enable IPO/LTO" ON)
    option(TemplateTest_WARNINGS_AS_ERRORS "Treat Warnings As Errors" ON)
    option(TemplateTest_ENABLE_CLANG_TIDY "Enable clang-tidy" ON)
    option(TemplateTest_ENABLE_CPPCHECK "Enable cpp-check analysis" ON)
    option(TemplateTest_ENABLE_CACHE "Enable ccache" ON)
  endif()
  if(NOT PROJECT_IS_TOP_LEVEL)
    mark_as_advanced(
      TemplateTest_ENABLE_IPO
      TemplateTest_WARNINGS_AS_ERRORS
      TemplateTest_ENABLE_CLANG_TIDY
      TemplateTest_ENABLE_CPPCHECK
      TemplateTest_ENABLE_CACHE)
  endif()

  # Sanitizers
  TemplateTest_supports_sanitizers()
  if(NOT PROJECT_IS_TOP_LEVEL
     OR NOT TemplateTest_ENABLE_DEVELOPER_MODE
     OR TemplateTest_PACKAGING_MAINTAINER_MODE)
    option(TemplateTest_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" OFF)
    option(TemplateTest_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(TemplateTest_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" OFF)
    option(TemplateTest_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(TemplateTest_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
  else()
    option(TemplateTest_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" ${SUPPORTS_ASAN})
    option(TemplateTest_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(TemplateTest_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" ${SUPPORTS_UBSAN})
    option(TemplateTest_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(TemplateTest_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
  endif()
  if(NOT PROJECT_IS_TOP_LEVEL)
    mark_as_advanced(
      TemplateTest_ENABLE_SANITIZER_ADDRESS
      TemplateTest_ENABLE_SANITIZER_LEAK
      TemplateTest_ENABLE_SANITIZER_UNDEFINED
      TemplateTest_ENABLE_SANITIZER_THREAD
      TemplateTest_ENABLE_SANITIZER_MEMORY)
  endif()

  # Fuzzer
  TemplateTest_check_libfuzzer_support(LIBFUZZER_SUPPORTED)
  if(LIBFUZZER_SUPPORTED
     AND (TemplateTest_ENABLE_SANITIZER_ADDRESS
          OR TemplateTest_ENABLE_SANITIZER_THREAD
          OR TemplateTest_ENABLE_SANITIZER_UNDEFINED))
    set(DEFAULT_FUZZER ON)
  else()
    set(DEFAULT_FUZZER OFF)
  endif()
  option(TemplateTest_BUILD_FUZZ_TESTS "Enable fuzz testing executable" ${DEFAULT_FUZZER})

endmacro()

macro(TemplateTest_global_options)
  if(TemplateTest_ENABLE_IPO)
    include(cmake/InterproceduralOptimization.cmake)
    TemplateTest_enable_ipo()
  endif()

  TemplateTest_supports_sanitizers()

  if(TemplateTest_ENABLE_HARDENING AND TemplateTest_ENABLE_GLOBAL_HARDENING)
    include(cmake/Hardening.cmake)
    if(NOT SUPPORTS_UBSAN
       OR TemplateTest_ENABLE_SANITIZER_UNDEFINED
       OR TemplateTest_ENABLE_SANITIZER_ADDRESS
       OR TemplateTest_ENABLE_SANITIZER_THREAD
       OR TemplateTest_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    message("${TemplateTest_ENABLE_HARDENING} ${ENABLE_UBSAN_MINIMAL_RUNTIME} ${TemplateTest_ENABLE_SANITIZER_UNDEFINED}")
    TemplateTest_enable_hardening(TemplateTest_options ON ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()
endmacro()

macro(TemplateTest_local_options)
  if(PROJECT_IS_TOP_LEVEL)
    include(cmake/StandardProjectSettings.cmake)
  endif()

  add_library(TemplateTest_warnings INTERFACE)
  add_library(TemplateTest_options INTERFACE)

  include(cmake/CompilerWarnings.cmake)
  TemplateTest_set_project_warnings(
    TemplateTest_warnings
    ${TemplateTest_WARNINGS_AS_ERRORS}
    ""
    ""
    ""
    "")

  if(TemplateTest_ENABLE_USER_LINKER)
    include(cmake/Linker.cmake)
    configure_linker(TemplateTest_options)
  endif()

  include(cmake/Sanitizers.cmake)
  TemplateTest_enable_sanitizers(
    TemplateTest_options
    ${TemplateTest_ENABLE_SANITIZER_ADDRESS}
    ${TemplateTest_ENABLE_SANITIZER_LEAK}
    ${TemplateTest_ENABLE_SANITIZER_UNDEFINED}
    ${TemplateTest_ENABLE_SANITIZER_THREAD}
    ${TemplateTest_ENABLE_SANITIZER_MEMORY})

  set_target_properties(TemplateTest_options PROPERTIES UNITY_BUILD ${TemplateTest_ENABLE_UNITY_BUILD})

  if(TemplateTest_ENABLE_PCH)
    target_precompile_headers(
      TemplateTest_options
      INTERFACE
      <vector>
      <string>
      <utility>)
  endif()

  if(TemplateTest_ENABLE_CACHE)
    include(cmake/Cache.cmake)
    TemplateTest_enable_cache()
  endif()

  include(cmake/StaticAnalyzers.cmake)
  if(TemplateTest_ENABLE_CLANG_TIDY)
    TemplateTest_enable_clang_tidy(TemplateTest_options ${TemplateTest_WARNINGS_AS_ERRORS})
  endif()

  if(TemplateTest_ENABLE_CPPCHECK)
    TemplateTest_enable_cppcheck(${TemplateTest_WARNINGS_AS_ERRORS} "" # override cppcheck options
    )
  endif()

  if(TemplateTest_ENABLE_COVERAGE)
    include(cmake/Tests.cmake)
    TemplateTest_enable_coverage(TemplateTest_options)
  endif()

  if(TemplateTest_WARNINGS_AS_ERRORS)
    check_cxx_compiler_flag("-Wl,--fatal-warnings" LINKER_FATAL_WARNINGS)
    if(LINKER_FATAL_WARNINGS)
      # This is not working consistently, so disabling for now
      # target_link_options(TemplateTest_options INTERFACE -Wl,--fatal-warnings)
    endif()
  endif()

  if(TemplateTest_ENABLE_HARDENING AND NOT TemplateTest_ENABLE_GLOBAL_HARDENING)
    include(cmake/Hardening.cmake)
    if(NOT SUPPORTS_UBSAN
       OR TemplateTest_ENABLE_SANITIZER_UNDEFINED
       OR TemplateTest_ENABLE_SANITIZER_ADDRESS
       OR TemplateTest_ENABLE_SANITIZER_THREAD
       OR TemplateTest_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    TemplateTest_enable_hardening(TemplateTest_options OFF ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()

endmacro()
