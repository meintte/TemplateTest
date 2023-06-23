add_executable(App main.cpp UserParameters.cpp App.cpp)

target_link_libraries(App PRIVATE TemplateTest::TemplateTest_options TemplateTest::TemplateTest_warnings)
target_link_system_libraries(
  App
  PRIVATE
  CLI11::CLI11
  fmt::fmt
  spdlog::spdlog
  Eigen3::Eigen)

target_include_directories(
  App ${WARNING_GUARD}
  PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include" $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
          $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>)

target_compile_features(App PUBLIC cxx_std_${CMAKE_CXX_STANDARD})

set_target_properties(
  App
  PROPERTIES VERSION ${PROJECT_VERSION}
             CXX_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN YES)
