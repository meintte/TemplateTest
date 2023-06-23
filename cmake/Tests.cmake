function(TemplateTest_enable_coverage project_name)
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    target_compile_options(${project_name} INTERFACE --coverage -O0 -g)
    target_link_libraries(${project_name} INTERFACE --coverage)
  endif()
endfunction()

function(add_constexpr_test TEST_NAME)
  cmake_parse_arguments(
    ADD_CONSTEXPR_TEST
    ""
    ""
    "SOURCES;LIBRARIES;SYSTEM_LIBRARIES"
    ${ARGN})

  add_executable(constexpr_${TEST_NAME} ${ADD_CONSTEXPR_TEST_SOURCES})
  target_link_libraries(
    constexpr_${TEST_NAME}
    PRIVATE TemplateTest::TemplateTest_warnings
            TemplateTest::TemplateTest_options
            Catch2::Catch2WithMain
            ${ADD_CONSTEXPR_TEST_LIBRARIES})
  target_link_system_libraries(constexpr_${TEST_NAME} PRIVATE ${ADD_CONSTEXPR_TEST_SYSTEM_LIBRARIES})

  catch_discover_tests(
    constexpr_${TEST_NAME}
    TEST_PREFIX
    "constexpr."
    REPORTER
    XML
    OUTPUT_DIR
    .
    OUTPUT_PREFIX
    "constexpr."
    OUTPUT_SUFFIX
    .xml)

  # Disable the constexpr portion of the test, and build again this allows us to
  # have an executable that we can debug when things go wrong with the constexpr
  # testing
  add_executable(relaxed_constexpr_${TEST_NAME} ${ADD_CONSTEXPR_TEST_SOURCES})
  target_link_libraries(
    relaxed_constexpr_${TEST_NAME}
    PRIVATE TemplateTest::TemplateTest_warnings
            TemplateTest::TemplateTest_options
            Catch2::Catch2WithMain
            ${ADD_CONSTEXPR_TEST_LIBRARIES})
  target_link_system_libraries(relaxed_constexpr_${TEST_NAME} PRIVATE ${ADD_CONSTEXPR_TEST_SYSTEM_LIBRARIES})

  target_compile_definitions(relaxed_constexpr_${TEST_NAME} PRIVATE -DCATCH_CONFIG_RUNTIME_STATIC_REQUIRE)

  catch_discover_tests(
    relaxed_constexpr_${TEST_NAME}
    TEST_PREFIX
    "relaxed_constexpr."
    REPORTER
    XML
    OUTPUT_DIR
    .
    OUTPUT_PREFIX
    "relaxed_constexpr."
    OUTPUT_SUFFIX
    .xml)
endfunction()

function(add_unit_test TEST_NAME)
  cmake_parse_arguments(
    ADD_UNIT_TEST
    ""
    ""
    "SOURCES;LIBRARIES;SYSTEM_LIBRARIES"
    ${ARGN})

  add_executable(test_${TEST_NAME} ${ADD_UNIT_TEST_SOURCES})
  target_link_libraries(
    test_${TEST_NAME}
    PRIVATE TemplateTest::TemplateTest_warnings
            TemplateTest::TemplateTest_options
            Catch2::Catch2WithMain
            ${ADD_UNIT_TEST_LIBRARIES})
  target_link_system_libraries(test_${TEST_NAME} PRIVATE ${ADD_UNIT_TEST_SYSTEM_LIBRARIES})

  if(WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(
      TARGET test_${TEST_NAME}
      PRE_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:test_${TEST_NAME}> $<TARGET_FILE_DIR:test_${TEST_NAME}>
      COMMAND_EXPAND_LISTS)
  endif()

  catch_discover_tests(
    test_${TEST_NAME}
    TEST_PREFIX
    "unittests."
    REPORTER
    XML
    OUTPUT_DIR
    .
    OUTPUT_PREFIX
    "unittests."
    OUTPUT_SUFFIX
    .xml)
endfunction()
