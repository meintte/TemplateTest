# Provide a simple smoke test to make sure that the CLI works and can display a
# --help message
add_test(NAME cli.has_help COMMAND App --help)

# Provide a test to verify that the version being reported from the application
# matches the version given to CMake. This will be important once you package
# your program. Real world shows that this is the kind of simple mistake that is
# easy to make, but also easy to test for.
add_test(NAME cli.version_matches COMMAND App --version)
set_tests_properties(cli.version_matches PROPERTIES PASS_REGULAR_EXPRESSION "${PROJECT_VERSION}")

# Sampler2d
add_unit_test(
  Sampler2d
  SOURCES
  test_Sampler2d.cpp
  LIBRARIES
  TemplateTest::Random
  SYSTEM_LIBRARIES
  Eigen3::Eigen)

# Grid
add_unit_test(
  Domain
  SOURCES
  test_Domain.cpp
  LIBRARIES
  TemplateTest::Grid)

add_unit_test(
  Boundary
  SOURCES
  test_Boundary.cpp
  LIBRARIES
  TemplateTest::Grid)

# Distributions
add_unit_test(
  Dirac
  SOURCES
  test_Dirac.cpp
  LIBRARIES
  TemplateTest::Distributions)

add_unit_test(
  MultiDirac
  SOURCES
  test_MultiDirac.cpp
  LIBRARIES
  TemplateTest::Distributions)

add_unit_test(
  Uniform
  SOURCES
  test_Uniform.cpp
  LIBRARIES
  TemplateTest::Distributions)

add_unit_test(
  Exponential
  SOURCES
  test_Exponential.cpp
  LIBRARIES
  TemplateTest::Distributions)

# Fractures
add_unit_test(
  Fracture
  SOURCES
  test_Fracture.cpp
  LIBRARIES
  TemplateTest::Fractures
  SYSTEM_LIBRARIES
  Eigen3::Eigen)

add_unit_test(
  FractureFromApertureFunction
  SOURCES
  test_FractureFromApertureFunction.cpp
  LIBRARIES
  TemplateTest::Fractures
  SYSTEM_LIBRARIES
  Eigen3::Eigen)

add_unit_test(
  Family
  SOURCES
  test_Family.cpp
  LIBRARIES
  TemplateTest::Fractures
  SYSTEM_LIBRARIES
  Eigen3::Eigen)

add_unit_test(
  Factory
  SOURCES
  test_Factory.cpp
  LIBRARIES
  TemplateTest::Fractures
  SYSTEM_LIBRARIES
  Eigen3::Eigen)
