// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.1
// LVGL version: 8.3.11
// Project name: sq_proj_1

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////


// SCREEN: ui_Hello_World
void ui_Hello_World_screen_init(void);
lv_obj_t *ui_Hello_World;
lv_obj_t *ui_Panel4;
void ui_event_Slider2( lv_event_t * e);
lv_obj_t *ui_Slider2;
lv_obj_t *ui_Chart1;
void ui_event_Slider1( lv_event_t * e);
lv_obj_t *ui_Slider1;
lv_obj_t *ui_Panel5;
lv_obj_t *ui_Panel6;
void ui_event_ImgButton3( lv_event_t * e);
lv_obj_t *ui_ImgButton3;
void ui_event_ImgButton1( lv_event_t * e);
lv_obj_t *ui_ImgButton1;
void ui_event_ImgButton2( lv_event_t * e);
lv_obj_t *ui_ImgButton2;
void ui_event_ImgButton4( lv_event_t * e);
lv_obj_t *ui_ImgButton4;
void ui_event_ImgButton5( lv_event_t * e);
lv_obj_t *ui_ImgButton5;
lv_obj_t *ui_TextArea1;
lv_obj_t *ui____initial_actions0;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 32
    #error "LV_COLOR_DEPTH should be 32bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_Slider2( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_VALUE_CHANGED) {
      slider_y_event_cb( e );
}
}
void ui_event_Slider1( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_VALUE_CHANGED) {
      slider_x_event_cb( e );
}
}
void ui_event_ImgButton3( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      button_0_event_cb( e );
}
}
void ui_event_ImgButton1( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      button_1_event_cb( e );
}
}
void ui_event_ImgButton2( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      button_2_event_cb( e );
}
}
void ui_event_ImgButton4( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      button_3_event_cb( e );
}
}
void ui_event_ImgButton5( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      button_4_event_cb( e );
}
}

///////////////////// SCREENS ////////////////////

void ui_init( void )
{LV_EVENT_GET_COMP_CHILD = lv_event_register_id();

lv_disp_t *dispp = lv_disp_get_default();
lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
lv_disp_set_theme(dispp, theme);
ui_Hello_World_screen_init();
ui____initial_actions0 = lv_obj_create(NULL);
lv_disp_load_scr( ui_Hello_World);
}
