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


/****************************************************************************
 * Definitions
 *****************************************************************************/


/****************************************************************************
 * Variables
 *****************************************************************************/

static uint32_t task_period;
static uint64_t next_task_tick;


/****************************************************************************
 * Prototypes
 *****************************************************************************/

static bool initialize_gui(void);

static void hal_init(void);


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

    // lv_tick_inc(task_period);

    // led_process();
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
