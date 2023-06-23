add_library(Grid INTERFACE)
add_library(TemplateTest::Grid ALIAS Grid)

target_link_libraries(Grid INTERFACE TemplateTest_options TemplateTest_warnings)

target_include_directories(Grid ${WARNING_GUARD} INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                                                           $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>)

target_compile_features(Grid INTERFACE cxx_std_${CMAKE_CXX_STANDARD})

set_target_properties(
  Grid
  PROPERTIES VERSION ${PROJECT_VERSION}
             CXX_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN YES)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(Grid INTERFACE Grid_STATIC_DEFINE)
endif()
