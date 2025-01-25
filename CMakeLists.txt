cmake_minimum_required(VERSION 3.31.4)

message("CMake v" ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION})

project(ProjectTheProject)

# option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
add_compile_options(-DHAVE_INLINE)

set(PTP_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PTP_OUTPUT_DIRECTORY})
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PTP_OUTPUT_DIRECTORY})

find_package(PkgConfig REQUIRED)

pkg_check_modules(GLIB REQUIRED IMPORTED_TARGET glib-2.0)
pkg_check_modules(GSL REQUIRED IMPORTED_TARGET gsl)
pkg_check_modules(SDL REQUIRED IMPORTED_TARGET sdl3)

add_subdirectory("GameTheGame")
