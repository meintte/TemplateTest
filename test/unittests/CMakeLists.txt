# Provide a simple smoke test to make sure that the CLI works and can display a
# --help message
add_test(NAME cli.has_help COMMAND App --help)

# Provide a test to verify that the version being reported from the application
# matches the version given to CMake. This will be important once you package
# your program. Real world shows that this is the kind of simple mistake that is
# easy to make, but also easy to test for.
add_test(NAME cli.version_matches COMMAND App --version)
set_tests_properties(cli.version_matches PROPERTIES PASS_REGULAR_EXPRESSION "${PROJECT_VERSION}")

add_executable(tests tests.cpp)
target_link_libraries(
  tests
  PRIVATE TemplateTest::TemplateTest_warnings
          TemplateTest::TemplateTest_options
          TemplateTest::Grid
          Catch2::Catch2WithMain)

if(WIN32 AND BUILD_SHARED_LIBS)
  add_custom_command(
    TARGET tests
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:tests> $<TARGET_FILE_DIR:tests>
    COMMAND_EXPAND_LISTS)
endif()

# automatically discover tests that are defined in catch based test files you
# can modify the unittests. Set TEST_PREFIX to whatever you want, or use
# different for different binaries
catch_discover_tests(
  tests
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
