include(cmake/CPM.cmake)

# Done as a function so that updates to variables like
# CMAKE_CXX_FLAGS don't propagate out to other
# targets
function(myproject_setup_dependencies)

  # For each dependency, see if it's
  # already been provided to us by a parent project

  if(NOT TARGET fmtlib::fmtlib)
    cpmaddpackage("gh:fmtlib/fmt#9.1.0")
  endif()

  if(NOT TARGET spdlog::spdlog)
    cpmaddpackage(
      NAME
      spdlog
      GITHUB_REPOSITORY
      "gabime/spdlog"
      VERSION
      1.11.0
      OPTIONS
      "SPDLOG_FMT_EXTERNAL ON"
      EXCLUDE_FROM_ALL
      YES)
  endif()

  if(NOT TARGET Catch2::Catch2WithMain)
    cpmaddpackage("gh:catchorg/Catch2@3.3.2")
  endif()

  if(NOT TARGET CLI11::CLI11)
    cpmaddpackage("gh:CLIUtils/CLI11@2.3.2")
  endif()

  if(NOT TARGET ftxui::screen)
    cpmaddpackage(
      NAME
      FTXUI
      GITHUB_REPOSITORY
      "ArthurSonzogni/FTXUI"
      GIT_TAG
      "v4.1.1"
      OPTIONS
      "FTXUI_BUILD_EXAMPLES OFF"
      "FTXUI_BUILD_DOCS OFF"
      "FTXUI_BUILD_TESTS OFF"
      "FTXUI_BUILD_TESTS_FUZZER OFF"
      "FTXUI_ENABLE_INSTALL OFF"
      EXCLUDE_FROM_ALL
      YES)
  endif()

  if(NOT TARGET tools::tools)
    cpmaddpackage("gh:lefticus/tools#update_build_system")
  endif()

  # if(NOT TARGET glfw::glfw)
  #   cpmaddpackage(
  #     NAME
  #     glfw
  #     GITHUB_REPOSITORY
  #     "glfw/glfw"
  #     GIT_TAG
  #     "3.3.8"
  #     OPTIONS
  #     "GLFW_BUILD_EXAMPLES OFF"
  #     "GLFW_BUILD_TESTS OFF"
  #     "GLFW_BUILD_DOCS OFF"
  #     "GLFW_INSTALL OFF"
  #     EXCLUDE_FROM_ALL
  #     YES)
  # endif()

  # if(NOT TARGET imgui::imgui)
  #   cpmaddpackage(
  #     NAME
  #     imgui
  #     GITHUB_REPOSITORY
  #     "ocornut/imgui"
  #     GIT_TAG
  #     "docking"
  #     EXCLUDE_FROM_ALL
  #     YES)
  # endif()

  if(NOT TARGET Eigen3::Eigen)
    cpmaddpackage(
      NAME
      Eigen
      GITLAB_REPOSITORY
      "libeigen/eigen"
      GIT_TAG
      "3.4.0"
      OPTIONS
      "EIGEN_BUILD_DOC OFF"
      "EIGEN_LEAVE_TEST_IN_ALL_TARGET OFF"
      "BUILD_TESTING OFF"
      "EIGEN_BUILD_PKGCONFIG OFF"
      "EIGEN_BUILD_BLAS OFF"
      "EIGEN_BUILD_LAPACK OFF"
      "EIGEN_BUILD_CMAKE_PACKAGE OFF"
      EXCLUDE_FROM_ALL
      YES
      SYSTEM
      YES)
  endif()

endfunction()
