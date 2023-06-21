include(GenerateExportHeader)

add_library(Random Sampler2d.cpp)

add_library(myproject::Random ALIAS Random)

target_link_libraries(Random PRIVATE myproject_options myproject_warnings)
target_link_system_libraries(Random PRIVATE Eigen3::Eigen)

target_include_directories(Random ${WARNING_GUARD} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                                                          $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>)

target_compile_features(Random PUBLIC cxx_std_${CMAKE_CXX_STANDARD})

set_target_properties(
  Random
  PROPERTIES VERSION ${PROJECT_VERSION}
             CXX_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN YES)

generate_export_header(Random EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/myproject/Random_export.hpp)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(Random PUBLIC Random_STATIC_DEFINE)
endif()
