include(GenerateExportHeader)

add_library(
  Distributions
  Dirac.cpp
  MultiDirac.cpp
  Uniform.cpp
  Exponential.cpp)

add_library(TemplateTest::Distributions ALIAS Distributions)

target_link_libraries(Distributions PRIVATE TemplateTest_options TemplateTest_warnings TemplateTest::Random)
target_link_system_libraries(Distributions PRIVATE Eigen3::Eigen)

target_include_directories(Distributions ${WARNING_GUARD} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                                                                 $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>)

target_compile_features(Distributions PUBLIC cxx_std_${CMAKE_CXX_STANDARD})

set_target_properties(
  Distributions
  PROPERTIES VERSION ${PROJECT_VERSION}
             CXX_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN YES)

generate_export_header(Distributions EXPORT_FILE_NAME
                       ${PROJECT_BINARY_DIR}/include/TemplateTest/Distributions_export.hpp)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(Distributions PUBLIC Distributions_STATIC_DEFINE)
endif()
