add_subdirectory(app)
add_subdirectory(gui)
add_subdirectory(buffer)
add_subdirectory(cli)
add_subdirectory(serial)
add_subdirectory(time_funcs)
add_subdirectory(lvgl)
include_directories(.)
include_directories(/opt/homebrew/opt/sdl2/include)

find_package(SDL2 REQUIRED)

target_include_directories(lvgl PUBLIC . ${SDL2_INCLUDE_DIRS})
target_link_libraries(lvgl ${SDL2_LIBRARIES})

add_executable(serial_tool main.c)
target_link_libraries(serial_tool app gui buffer cli serial time_funcs lvgl)