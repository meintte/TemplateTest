include(cmake/CPM.cmake)

# Done as a function so that updates to variables like
# CMAKE_CXX_FLAGS don't propagate out to other
# targets
function(TemplateTest_setup_dependencies)

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

  if(NOT TARGET Eigen3::Eigen)
    find_package(Eigen3 3.3 NO_MODULE)
    if(NOT Eigen3_FOUND)
      message(AUTHOR_WARNING "Adding Eigen as a CPM dependency.")
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
  endif()

endfunction()
