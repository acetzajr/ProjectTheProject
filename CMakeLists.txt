cmake_minimum_required(VERSION 3.31.4)

project(ProjectTheProject)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

add_compile_options(-Wfatal-errors -DHAVE_INLINE)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GLIB2 REQUIRED IMPORTED_TARGET glib-2.0)
pkg_check_modules(GSL REQUIRED IMPORTED_TARGET gsl)
pkg_check_modules(SDL3 REQUIRED IMPORTED_TARGET sdl3)
pkg_check_modules(CAIRO REQUIRED IMPORTED_TARGET cairo)

add_subdirectory("GameTheGame")
