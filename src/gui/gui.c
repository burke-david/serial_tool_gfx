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
#include "../time_funcs/time_funcs.h"
#include "../lvgl/lvgl.h"
#include "../lv_drivers/sdl/sdl.h"
#include "../ui/ui.h"
#include <stdio.h>
#include "../buffer/ring_buf.h"


/****************************************************************************
 * Definitions
 *****************************************************************************/

#define PLOT_DATA_ELEMENTS 100U

/****************************************************************************
 * Variables
 *****************************************************************************/

static uint32_t task_period;
static uint64_t next_task_tick;

static lv_chart_series_t *chart_series;

static ring_buf_t plot_buffer;
static lv_coord_t plot_data[PLOT_DATA_ELEMENTS];
static uint32_t plot_data_index = 0;

/****************************************************************************
 * Prototypes
 *****************************************************************************/

static bool initialize_gui(void);

static void hal_init(void);

static void _ui_textarea_append_text(lv_obj_t *textarea, const char *text);

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

    if (NULL == ui_Chart1){
        printf("ui_Chart1 doesn't exist\n");
        return false;
    }

    // Initialize the plot buffer
    ring_buf_init(&plot_buffer, plot_data, PLOT_DATA_ELEMENTS, sizeof(lv_coord_t));

    // grab a pointer to the data series in the chart
    chart_series = lv_chart_get_series_next(ui_Chart1, NULL);

    // Remove the current series from the chart and add a new one
    if (NULL != chart_series) {
        lv_chart_remove_series(ui_Chart1, chart_series);
    }
    
    lv_chart_set_point_count(ui_Chart1, PLOT_DATA_ELEMENTS);
    lv_chart_series_t *new_series = lv_chart_add_series(ui_Chart1, lv_color_hex(0x00FF00), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_set_ext_y_array(ui_Chart1, new_series, plot_data);

    lv_chart_refresh(ui_Chart1);

    // // clear the data from the series. Check for null before doing so.
    // if (chart_series != NULL){
    //     lv_chart_set_point_count(ui_Chart1, 0);
    //     lv_chart_set_point_count(ui_Chart1, 100);
    //     lv_chart_set_update_mode(ui_Chart1, LV_CHART_UPDATE_MODE_CIRCULAR);
    //     /* The following line causes the text area to disappear and not function... LOL!! */
    //     // lv_chart_set_all_value(ui_Chart1, chart_series, 0);
    // }
    // else{
    //     chart_series = lv_chart_add_series(ui_Chart1, lv_color_hex(0x00FF00), LV_CHART_AXIS_PRIMARY_Y);
    //     if (NULL == chart_series){
    //         printf("chart_series is NULL\n");
    //         return false;
    //     }
    // }

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

    // lv_tick_inc(task_period);

    // led_process();
}

void gui_process_byte(uint8_t byte)
{
    // convert the byte to a string pointer that can be passed to the _ui_textarea_append_text function
    char byte_str[4];
    snprintf(byte_str, sizeof(byte_str), "%02X ", byte);

    lv_coord_t data;

    // call the _ui_textarea_append_text function to add the byte to the text area
    _ui_textarea_append_text(ui_TextArea1, byte_str);

    // Add the byte to the plot buffer
    data = (lv_coord_t)(0x000000FF & byte);
    ring_buf_push(&plot_buffer, &data);
    lv_chart_refresh(ui_Chart1);

    plot_data_index++;
    if (plot_data_index >= PLOT_DATA_ELEMENTS){
        plot_data_index = 0;
        ring_buf_clear(&plot_buffer);

        // set all data in the plot_data array to 0
        for (uint32_t i = 0; i < PLOT_DATA_ELEMENTS; i++){
            plot_data[i] = 0;
        }
    }

}

static bool initialize_gui(void)
{
    bool status = true;

    lv_init();

    /*Initialize the HAL (display, input devices, tick) for LVGL*/
    hal_init();

    ui_init();

    return (status);
}

void _ui_textarea_append_text(lv_obj_t *textarea, const char *text)
{
    lv_textarea_add_text(textarea, text);
}

/**
 * Initialize the Hardware Abstraction Layer (HAL) for LVGL
 */
static void hal_init(void)
{
  /* Use the 'monitor' driver which creates window on PC's monitor to simulate a display*/
  sdl_init();

  /*Create a display buffer*/
  static lv_color_t buf[SDL_HOR_RES * SDL_VER_RES];
  static lv_disp_draw_buf_t disp_draw_buf;
  lv_disp_draw_buf_init(&disp_draw_buf, buf, NULL, SDL_HOR_RES * SDL_VER_RES);

  /*Create a display*/
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv); /*Basic initialization*/
  disp_drv.draw_buf = &disp_draw_buf;
  disp_drv.flush_cb = sdl_display_flush;
  disp_drv.hor_res = SDL_HOR_RES;
  disp_drv.ver_res = SDL_VER_RES;
  lv_disp_drv_register(&disp_drv);

  /* Add a mouse as input device */
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv); /*Basic initialization*/
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = sdl_mouse_read;
  lv_indev_drv_register(&indev_drv);
}
