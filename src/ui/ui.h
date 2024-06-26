// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.1
// LVGL version: 8.3.11
// Project name: sq_proj_1

#ifndef _SQ_PROJ_1_UI_H
#define _SQ_PROJ_1_UI_H

#ifdef __cplusplus
extern "C" {
#endif

    #include "../lvgl/lvgl.h"

#include "ui_helpers.h"
#include "components/ui_comp.h"
#include "components/ui_comp_hook.h"
#include "ui_events.h"
#include "ui_theme_manager.h"
#include "ui_themes.h"

// SCREEN: ui_Hello_World
void ui_Hello_World_screen_init(void);
extern lv_obj_t *ui_Hello_World;
extern lv_obj_t *ui_Panel4;
void ui_event_Slider2( lv_event_t * e);
extern lv_obj_t *ui_Slider2;
extern lv_obj_t *ui_Chart1;
void ui_event_Slider1( lv_event_t * e);
extern lv_obj_t *ui_Slider1;
extern lv_obj_t *ui_Panel5;
extern lv_obj_t *ui_Panel6;
void ui_event_ImgButton3( lv_event_t * e);
extern lv_obj_t *ui_ImgButton3;
void ui_event_ImgButton1( lv_event_t * e);
extern lv_obj_t *ui_ImgButton1;
void ui_event_ImgButton2( lv_event_t * e);
extern lv_obj_t *ui_ImgButton2;
void ui_event_ImgButton4( lv_event_t * e);
extern lv_obj_t *ui_ImgButton4;
void ui_event_ImgButton5( lv_event_t * e);
extern lv_obj_t *ui_ImgButton5;
extern lv_obj_t *ui_TextArea1;
extern lv_obj_t *ui____initial_actions0;

LV_IMG_DECLARE( ui_img_stainless_circle_50px_green_off_png);   // assets/stainless_circle_50px_green_off.png
LV_IMG_DECLARE( ui_img_stainless_circle_50px_green_on_png);   // assets/stainless_circle_50px_green_on.png


LV_FONT_DECLARE( ui_font_Courier_New_16);


void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
