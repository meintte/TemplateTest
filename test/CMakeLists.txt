cmake_minimum_required(VERSION 3.15...3.23)

project(CmakeConfigPackageTests LANGUAGES CXX)

# ---- Test as standalone project the exported config package ----

if(PROJECT_IS_TOP_LEVEL OR TEST_INSTALLED_VERSION)
  enable_testing()

  find_package(TemplateTest CONFIG REQUIRED) # for App, project_options, ...

  if(NOT TARGET TemplateTest_options)
    message(FATAL_ERROR "Requiered config package not found!")
    return() # be strictly paranoid for Template Janitor github action! CK
  endif()
endif()

# ---- Dependencies ----

include(${Catch2_SOURCE_DIR}/extras/Catch.cmake)
include(../cmake/Tests.cmake)

# ---- Tests ----
add_subdirectory(constexpr)
add_subdirectory(unittests)
