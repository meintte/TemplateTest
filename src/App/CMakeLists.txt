add_executable(App main.cpp)

target_link_libraries(App PRIVATE TemplateTest::TemplateTest_options TemplateTest::TemplateTest_warnings)
target_link_system_libraries(
  App
  PRIVATE
  CLI11::CLI11
  fmt::fmt
  spdlog::spdlog
  Eigen3::Eigen)

target_include_directories(App PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")
