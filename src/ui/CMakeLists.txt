SET(SOURCES components/ui_comp_button1.c
    components/ui_comp.c
    screens/ui_Hello_World.c
    ui_theme_manager.c
    ui_themes.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.c
    images/ui_img_stainless_circle_50px_green_off_png.c
    images/ui_img_stainless_circle_50px_green_on_png.c
    fonts/ui_font_Courier_New_16.c)

add_library(ui ${SOURCES})
