cmake_minimum_required(VERSION 3.20)

project(ProjectTheProject)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(PTP_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PTP_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PTP_OUTPUT_DIRECTORY})

find_package(PkgConfig REQUIRED)

pkg_check_modules(GLIB REQUIRED IMPORTED_TARGET glib-2.0)
find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)

add_subdirectory("PepeThePepe")
add_subdirectory("GameTheGame")
