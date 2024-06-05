find_package(SDL2 REQUIRED SDL2)
include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}/../
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/lvgl
    ${PROJECT_SOURCE_DIR}/src/lv_drivers
    ${PROJECT_SOURCE_DIR}/src/ui
    ${PROJECT_SOURCE_DIR}/src/app
    ${PROJECT_SOURCE_DIR}/src/buffer 
    ${PROJECT_SOURCE_DIR}/src/cli 
    ${PROJECT_SOURCE_DIR}/src/gui 
    ${PROJECT_SOURCE_DIR}/src/serial 
    ${PROJECT_SOURCE_DIR}/src/time_funcs 
)

FILE(GLOB_RECURSE LVGL_Sources CONFIGURE_DEPENDS lvgl/*.c)
FILE(GLOB_RECURSE LV_DRIVERS_Sources CONFIGURE_DEPENDS lv_drivers/*.c)
FILE(GLOB_RECURSE UI_Sources CONFIGURE_DEPENDS ui/*.c ui/*.cpp)

# Create variables for the sources in my app, gui, and time_funcs directories
FILE(GLOB_RECURSE APP_Sources CONFIGURE_DEPENDS app/*.c app/*.cpp)
FILE(GLOB_RECURSE GUI_Sources CONFIGURE_DEPENDS gui/*.c gui/*.cpp)
FILE(GLOB_RECURSE TIME_FUNCS_Sources CONFIGURE_DEPENDS time_funcs/*.c time_funcs/*.cpp)
FILE(GLOB_RECURSE BUFFER_Sources CONFIGURE_DEPENDS buffer/*.c buffer/*.cpp)
FILE(GLOB_RECURSE CLI_Sources CONFIGURE_DEPENDS cli/*.c cli/*.cpp)
FILE(GLOB_RECURSE SERIAL_Sources CONFIGURE_DEPENDS serial/*.c serial/*.cpp)

add_executable(${PROJECT_NAME} 
    main.c 
    ${BUFFER_Sources} 
    ${CLI_Sources} 
    ${SERIAL_Sources} 
    ${APP_Sources} 
    ${GUI_Sources} 
    ${TIME_FUNCS_Sources} 
    ${LVGL_Sources} 
    ${LV_DRIVERS_Sources} 
    ${UI_Sources}
)

#string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)

target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES} m)