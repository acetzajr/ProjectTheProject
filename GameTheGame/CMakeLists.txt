file(GLOB_RECURSE SOURCE "source/*.c" "source/*.h")

add_executable(gtg ${SOURCE})

target_link_libraries(gtg PRIVATE SDL3::SDL3)
