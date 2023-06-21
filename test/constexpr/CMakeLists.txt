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
            ${ADD_CONSTEXPR_TEST_LIBRARIES}
            Catch2::Catch2WithMain)
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
            ${ADD_CONSTEXPR_TEST_LIBRARIES}
            Catch2::Catch2WithMain)
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

# Add the tests
add_constexpr_test(
  tests
  SOURCES
  constexpr_tests.cpp
  LIBRARIES
  TemplateTest::sample_library)
