file(GLOB_RECURSE SOURCE "source/*.c" "include/*.h")

add_library(PepeThePepe ${SOURCE})

target_include_directories(PepeThePepe PUBLIC "include" "private")

target_link_libraries(PepeThePepe PRIVATE SDL3::SDL3 PkgConfig::GLIB)
