cmake_minimum_required(VERSION 3.12)
project(template)

include(cmake/Common.cmake)

find_package(glfw 3.3 QUIET)
find_package(OpenGL REQUIRED)
#find_package(Eigen3 3.3 REQUIRED NO_MODULE)

add_subdirectory(external)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Make an interface targets that will carry standard project settings
add_library(project_options INTERFACE)
add_library(project_warnings INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)

include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

include(cmake/Doxygen.cmake)
enable_doxygen()

include(cmake/StaticAnalyzers.cmake)

option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" OFF)

add_subdirectory(src)
