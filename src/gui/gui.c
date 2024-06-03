/*
 * MIT License
 * 
 * Copyright (c) 2024 David Burke
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * File        gui.c
 * Created by  David Burke
 * Version     1.0
 * 
 */

#include "gui.h"
#include "led.h"
#include "../time_funcs/time_funcs.h"
#include "../lvgl/lvgl.h"
#include <stdio.h>



/****************************************************************************
 * Definitions
 *****************************************************************************/

typedef enum {
    DISP_SMALL,
    DISP_MEDIUM,
    DISP_LARGE,
} disp_size_t;

/****************************************************************************
 * Variables
 *****************************************************************************/

static uint32_t task_period;
static uint64_t next_task_tick;

static disp_size_t disp_size;

/* Tab-View object */
static lv_obj_t *tv;

static lv_style_t style_text_muted;
static lv_style_t style_title;
static lv_style_t style_icon;
static lv_style_t style_bullet;

static const lv_font_t *font_large;
static const lv_font_t *font_normal;

/* LEDs */
lv_obj_t *led1;
lv_obj_t *led2;
lv_obj_t *led3;

/* Tabs */
lv_obj_t *t1;
lv_obj_t *t2;
lv_obj_t *t3;
/****************************************************************************
 * Prototypes
 *****************************************************************************/

static bool initialize_gui(void);

static lv_display_t * hal_init(int32_t w, int32_t h);

static void create_tab_view(void);

static void tabview_delete_event_cb(lv_event_t * e);

static void create_led_in_tab(lv_obj_t *tab);

/****************************************************************************
 * Functions
 *****************************************************************************/

bool gui_init(uint32_t process_period)
{
    bool status = true;

    task_period = process_period;
    next_task_tick = get_millis() + task_period;

    status = initialize_gui();

    // create_tab_view();

    return status;
}

void gui_task(void)
{
    uint64_t now = get_millis();
    if (now < next_task_tick){
        return;
    }

    next_task_tick = (now + task_period);

    lv_timer_handler();

    lv_tick_inc(task_period);

    led_process();
}

static bool initialize_gui(void)
{
    bool status = true;
    lv_display_t* disp;

    lv_init();

    /*Initialize the HAL (display, input devices, tick) for LVGL*/
    disp = hal_init(480, 272);

    return (NULL != disp);
}

/**
 * Initialize the Hardware Abstraction Layer (HAL) for the LVGL graphics
 * library
 */
static lv_display_t *hal_init(int32_t w, int32_t h)
{
    lv_group_set_default(lv_group_create());

    lv_display_t *disp = lv_sdl_window_create(w, h);

    /* Set the window title */
    lv_sdl_window_set_title(disp, "Graphics Evaluation");

    lv_indev_t *mouse = lv_sdl_mouse_create();
    lv_indev_set_group(mouse, lv_group_get_default());
    lv_indev_set_display(mouse, disp);
    lv_display_set_default(disp);

    LV_IMAGE_DECLARE(mouse_cursor_icon); /*Declare the image file.*/
    lv_obj_t * cursor_obj;
    cursor_obj = lv_image_create(lv_screen_active()); /*Create an image object for the cursor */
    lv_image_set_src(cursor_obj, &mouse_cursor_icon);           /*Set the image source*/
    lv_indev_set_cursor(mouse, cursor_obj);             /*Connect the image  object to the driver*/

    lv_indev_t *mousewheel = lv_sdl_mousewheel_create();
    lv_indev_set_display(mousewheel, disp);
    lv_indev_set_group(mousewheel, lv_group_get_default());

    lv_indev_t *kb = lv_sdl_keyboard_create();
    lv_indev_set_display(kb, disp);
    lv_indev_set_group(kb, lv_group_get_default());

    return disp;
}

static void create_tab_view(void)
{
    if(LV_HOR_RES <= 320) disp_size = DISP_SMALL;
    else if(LV_HOR_RES < 720) disp_size = DISP_MEDIUM;
    else disp_size = DISP_LARGE;

    font_large = LV_FONT_DEFAULT;
    font_normal = LV_FONT_DEFAULT;

    int32_t tab_h;
    if(disp_size == DISP_LARGE) {
        tab_h = 70;
#if LV_FONT_MONTSERRAT_24
        font_large     = &lv_font_montserrat_24;
#else
        LV_LOG_WARN("LV_FONT_MONTSERRAT_24 is not enabled for the widgets demo. Using LV_FONT_DEFAULT instead.");
#endif
#if LV_FONT_MONTSERRAT_16
        font_normal    = &lv_font_montserrat_16;
#else
        LV_LOG_WARN("LV_FONT_MONTSERRAT_16 is not enabled for the widgets demo. Using LV_FONT_DEFAULT instead.");
#endif
    }
    else if(disp_size == DISP_MEDIUM) {
        tab_h = 45;
#if LV_FONT_MONTSERRAT_20
        font_large     = &lv_font_montserrat_20;
#else
        LV_LOG_WARN("LV_FONT_MONTSERRAT_20 is not enabled for the widgets demo. Using LV_FONT_DEFAULT instead.");
#endif
#if LV_FONT_MONTSERRAT_14
        font_normal    = &lv_font_montserrat_14;
#else
        LV_LOG_WARN("LV_FONT_MONTSERRAT_14 is not enabled for the widgets demo. Using LV_FONT_DEFAULT instead.");
#endif
    }
    else {   /* disp_size == DISP_SMALL */
        tab_h = 45;
#if LV_FONT_MONTSERRAT_18
        font_large     = &lv_font_montserrat_18;
#else
        LV_LOG_WARN("LV_FONT_MONTSERRAT_18 is not enabled for the widgets demo. Using LV_FONT_DEFAULT instead.");
#endif
#if LV_FONT_MONTSERRAT_12
        font_normal    = &lv_font_montserrat_12;
#else
        LV_LOG_WARN("LV_FONT_MONTSERRAT_12 is not enabled for the widgets demo. Using LV_FONT_DEFAULT instead.");
#endif
    }

#if LV_USE_THEME_DEFAULT
    lv_theme_default_init(NULL, lv_palette_main(LV_PALETTE_GREY), lv_palette_main(LV_PALETTE_RED), LV_THEME_DEFAULT_DARK,
                          font_normal);
#endif

    lv_style_init(&style_text_muted);
    lv_style_set_text_opa(&style_text_muted, LV_OPA_50);

    lv_style_init(&style_title);
    lv_style_set_text_font(&style_title, font_large);

    lv_style_init(&style_icon);
    lv_style_set_text_color(&style_icon, lv_theme_get_color_primary(NULL));
    lv_style_set_text_font(&style_icon, font_large);

    lv_style_init(&style_bullet);
    lv_style_set_border_width(&style_bullet, 0);
    lv_style_set_radius(&style_bullet, LV_RADIUS_CIRCLE);

    tv = lv_tabview_create(lv_screen_active());
    lv_tabview_set_tab_bar_size(tv, tab_h);
    lv_obj_add_event_cb(tv, tabview_delete_event_cb, LV_EVENT_DELETE, NULL);

    lv_obj_set_style_text_font(lv_screen_active(), font_normal, 0);

    t1 = lv_tabview_add_tab(tv, "Tab 1");
    t2 = lv_tabview_add_tab(tv, "Tab 2");
    t3 = lv_tabview_add_tab(tv, "Tab 3");

    if(disp_size == DISP_LARGE) {
        lv_obj_t *tab_bar = lv_tabview_get_tab_bar(tv);
        lv_obj_set_style_pad_left(tab_bar, LV_HOR_RES / 2, 0);
        // lv_obj_t * logo = lv_image_create(tab_bar);
        // lv_obj_add_flag(logo, LV_OBJ_FLAG_IGNORE_LAYOUT);
        // LV_IMAGE_DECLARE(img_lvgl_logo);
        // lv_image_set_src(logo, &img_lvgl_logo);
        // lv_obj_align(logo, LV_ALIGN_LEFT_MID, -LV_HOR_RES / 2 + 25, 0);

        lv_obj_t * label = lv_label_create(tab_bar);
        lv_obj_add_style(label, &style_title, 0);
        lv_obj_add_flag(label, LV_OBJ_FLAG_IGNORE_LAYOUT);
        lv_label_set_text_fmt(label, "LVGL v%d.%d.%d", lv_version_major(), lv_version_minor(), lv_version_patch());
        // lv_obj_align_to(label, logo, LV_ALIGN_OUT_RIGHT_TOP, 10, 0);

        label = lv_label_create(tab_bar);
        lv_label_set_text(label, "Widgets demo");
        lv_obj_add_flag(label, LV_OBJ_FLAG_IGNORE_LAYOUT);
        lv_obj_add_style(label, &style_text_muted, 0);
        // lv_obj_align_to(label, logo, LV_ALIGN_OUT_RIGHT_BOTTOM, 10, 0);
    }
}


static void tabview_delete_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_DELETE) {
        lv_style_reset(&style_text_muted);
        lv_style_reset(&style_title);
        lv_style_reset(&style_icon);
        lv_style_reset(&style_bullet);
    }
}

static void create_led_in_tab(lv_obj_t *tab)
{
    /* Create the led in the tab passed to the function */
    led1 = lv_led_create(tab);

    /* Align object to center of window, then set the position from the center x=-80 from center, y=0 from center */
    lv_obj_align(led1, LV_ALIGN_CENTER, -80, 0);

    lv_led_set_color(led1, lv_palette_main(LV_PALETTE_GREEN));
    lv_led_set_brightness(led1, 255);
    lv_led_on(led1);
}
