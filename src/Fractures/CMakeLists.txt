include(GenerateExportHeader)

add_library(Fractures Fracture.cpp Family.cpp Factory.cpp)

add_library(TemplateTest::Fractures ALIAS Fractures)

target_link_libraries(Fractures PRIVATE TemplateTest_options TemplateTest_warnings)
target_link_system_libraries(Fractures PRIVATE Eigen3::Eigen)

target_include_directories(Fractures ${WARNING_GUARD} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                                                             $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>)

target_compile_features(Fractures PUBLIC cxx_std_${CMAKE_CXX_STANDARD})

set_target_properties(
  Fractures
  PROPERTIES VERSION ${PROJECT_VERSION}
             CXX_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN YES)

generate_export_header(Fractures EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/TemplateTest/Fractures_export.hpp)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(Fractures PUBLIC Fractures_STATIC_DEFINE)
endif()
