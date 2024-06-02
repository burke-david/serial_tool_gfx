/**
 * @file led.c
 * @author david burke
 * @brief lvgl led handler
 */

#include <pthread.h>
#include "led.h"
#include "../time_funcs/time_funcs.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

/*****************************************************************************
 * Definitions
 *****************************************************************************/

#define LED_DEFAULT_OFF_BRIGHTNESS 150u
#define LED_DEFAULT_ON_BRIGHTNESS  255u
#define LED_DEFAULT_DUTY 0.5f

/* larger=slower change in brightness */
#define LED_BREATHING_SMOOTHNESS_PTS    250.0f
/* affects the width of peak (more or less darkness) */
#define LED_BREATHING_GAMMA             0.25f //0.14f
/* shifts the gaussian to be symmetric */
#define LED_BREATHING_BETA              0.5f

/*****************************************************************************
 * Variables
 *****************************************************************************/

static uint32_t led_count = 0;

static led_t leds[LED_MAX_COUNT];

static pthread_mutex_t lock;

/*****************************************************************************
 * Prototypes
 *****************************************************************************/

void my_keyboard_cb(lv_event_t * e);




/*****************************************************************************
 * Functions
 *****************************************************************************/

led_t *led_create(const lv_obj_t *parent, lv_align_t align, int32_t x_ofs, int32_t y_ofs, lv_palette_t color)
{
    if (led_count >= LED_MAX_COUNT) {
        printf("led_create: led_count >= LED_MAX_COUNT\n");
        return NULL;
    }

    if (NULL == parent)
        return NULL;

    pthread_mutex_lock(&lock);

    leds[led_count].led = lv_led_create(parent);
    lv_obj_align(leds[led_count].led, align, x_ofs, y_ofs);
    lv_led_set_color(leds[led_count].led, lv_palette_main(color));
    lv_led_set_brightness(leds[led_count].led, LED_DEFAULT_OFF_BRIGHTNESS);

    leds[led_count].align = align;
    leds[led_count].x_ofs = x_ofs;
    leds[led_count].y_ofs = y_ofs;
    leds[led_count].color = color;

    /* add a keyboard event to the led */
    lv_obj_add_event_cb(leds[led_count].led, my_keyboard_cb, LV_EVENT_ALL, NULL);
    lv_group_add_obj(lv_group_get_default(), leds[led_count].led);

    led_count++;

    pthread_mutex_unlock(&lock);
    return &leds[led_count-1];
}

void led_set_mode(led_t *led, led_mode_t mode, uint32_t period, float duty)
{
    if (NULL == led)
        return;

    pthread_mutex_lock(&lock);

    if (mode >= LED_MODE_MAX)
        led->mode = LED_MODE_OFF;
    else
        led->mode = mode;

    switch(mode)
    {
    case LED_MODE_ON:
        lv_led_set_brightness(led->led, led->on_bright);
        break;

    case LED_MODE_FLASHING:

        led->period = period;
        if ((duty > 0.0) && (duty < 1.0)) {
            led->duty = duty;
        }
        else {
            led->duty = LED_DEFAULT_DUTY;
        }

        lv_led_set_brightness(led->led, led->on_bright);
        led->is_on = true;
        led->on_timestamp = get_millis();
        led->off_timestamp = get_millis() + (uint64_t)((float)led->period * led->duty);

        break;

    case LED_MODE_BREATHING:
        led->breath_bright = 0;
        led->breath_index = 0;
        lv_led_set_brightness(led->led, led->breath_bright);
        break;

    case LED_MODE_OFF:
    default:
        lv_led_set_brightness(led->led, led->off_bright);
        break;
    }

    pthread_mutex_unlock(&lock);
}

void led_set_size(led_t *led, int32_t w, int32_t h)
{
    lv_obj_set_size(led->led, w, h);
}

void led_set_color(led_t *led, lv_palette_t color)
{
    if (NULL == led)
        return;

    pthread_mutex_lock(&lock);
    led->color = color;
    lv_led_set_color(led->led, lv_palette_main(color));
    pthread_mutex_unlock(&lock);
}

void led_set_brightness(led_t *led, uint8_t on_bright, uint8_t off_bright)
{
    if (NULL == led)
        return;

    pthread_mutex_lock(&lock);
    led->on_bright = on_bright;
    led->off_bright = off_bright;
    pthread_mutex_unlock(&lock);
}

bool led_get_position(const led_t *led, lv_point_t *pos)
{
    if (NULL == led)
        return false;

    if (NULL == pos)
        return false;

    pos->x = lv_obj_get_x(led->led);
    pos->y = lv_obj_get_y(led->led);

    return true;
}


bool led_move_x(led_t *led, int32_t offset)
{
    if (NULL == led)
        return false;

    pthread_mutex_lock(&lock);

    int32_t current_x = lv_obj_get_x(led->led);
    int32_t current_y = lv_obj_get_y(led->led);

    if (led->align != LV_ALIGN_DEFAULT) {
        printf("led's alignment will be changed to LV_ALIGN_DEFAULT\n");
        led->align = LV_ALIGN_DEFAULT;
        led->x_ofs = current_x;
        led->y_ofs = current_y;
        lv_obj_align(led->led, led->align, led->x_ofs, led->y_ofs);
    }

    int32_t new_x = current_x + offset;

    lv_obj_t *parent = lv_obj_get_parent(led->led);
    int32_t parent_width = lv_obj_get_width(parent);

    if (new_x < 0) {
        new_x = 0;
    } else if (new_x + lv_obj_get_width(led->led) > parent_width) {
        new_x = parent_width - lv_obj_get_width(led->led);
    }

    lv_obj_set_x(led->led, new_x);

    pthread_mutex_unlock(&lock);

    return true;
}

bool led_move_y(led_t *led, int32_t offset)
{
    if (NULL == led)
        return false;

    pthread_mutex_lock(&lock);

    int32_t current_x = lv_obj_get_x(led->led);
    int32_t current_y = lv_obj_get_y(led->led);

    if (led->align != LV_ALIGN_DEFAULT) {
        printf("led's alignment will be changed to LV_ALIGN_DEFAULT\n");
        led->align = LV_ALIGN_DEFAULT;
        led->x_ofs = current_x;
        led->y_ofs = current_y;
        lv_obj_align(led->led, led->align, led->x_ofs, led->y_ofs);
    }

    int32_t new_y = current_y + offset;

    lv_obj_t *parent = lv_obj_get_parent(led->led);
    int32_t parent_height = lv_obj_get_height(parent);

    if (new_y < 0) {
        new_y = 0;
    } else if (new_y + lv_obj_get_height(led->led) > parent_height) {
        new_y = parent_height - lv_obj_get_height(led->led);
    }

    lv_obj_set_y(led->led, new_y);

    pthread_mutex_unlock(&lock);

    return true;
}

void led_rotate(led_t *led)
{
    if (NULL == led)
        return;

    pthread_mutex_lock(&lock);

    /* Get the current height and width of the led object */
    int32_t width = lv_obj_get_width(led->led);
    int32_t height = lv_obj_get_height(led->led);

    /* Rotate the led object by flipping the height and width */
    lv_obj_set_size(led->led, height, width);


    pthread_mutex_unlock(&lock);
}

void led_init(void)
{
    led_count = 0;
    for (uint32_t i=0; i<LED_MAX_COUNT; i++) {
        leds[i].led = NULL;
        leds[i].mode = LED_MODE_OFF;
        leds[i].align = LV_ALIGN_CENTER;
        leds[i].color = LV_PALETTE_RED;
        leds[i].off_bright = LED_DEFAULT_OFF_BRIGHTNESS;
        leds[i].on_bright = LED_DEFAULT_ON_BRIGHTNESS;
        leds[i].duty = LED_DEFAULT_DUTY;
        leds[i].breath_index = 0;
        leds[i].breath_bright = 0;
        leds[i].parent = NULL;
        leds[i].period = 0;
        leds[i].x_ofs = 0;
        leds[i].y_ofs = 0;
        leds[i].is_on = false;
    }

    /* create a mutex to protect leds data */
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("\n mutex init has failed\n");
        return;
    }
}


void led_process(void)
{
    uint64_t now;

    pthread_mutex_lock(&lock);
    for (int i=0; i<LED_MAX_COUNT; i++) {
        if (leds[i].led != NULL) {
            if (leds[i].mode == LED_MODE_FLASHING) {
                now = get_millis();

                if(leds[i].is_on && (now >= leds[i].off_timestamp)) {
                    /* turn off the led */
                    lv_led_set_brightness(leds[i].led, leds[i].off_bright);
                    leds[i].is_on = false;
                }
                else if(!leds[i].is_on && ((now - leds[i].on_timestamp) >= leds[i].period)) {
                    /* turn on the led */
                    lv_led_set_brightness(leds[i].led, leds[i].on_bright);
                    leds[i].is_on = true;
                    /* calculate the off timestamp and capture the on_timestamp */
                    leds[i].on_timestamp = now;
                    leds[i].off_timestamp = now + (uint64_t)((float)leds[i].period * leds[i].duty);
                }
            }
            else if (leds[i].mode == LED_MODE_BREATHING) {
                leds[i].breath_bright = (uint8_t)(255.0*(exp(-(pow((((float)leds[i].breath_index++/LED_BREATHING_SMOOTHNESS_PTS)-LED_BREATHING_BETA)/LED_BREATHING_GAMMA,2.0))/2.0)));
                if (leds[i].breath_index >= LED_BREATHING_SMOOTHNESS_PTS) {
                    leds[i].breath_index = 0;
                }
                lv_led_set_brightness(leds[i].led, leds[i].breath_bright);
            }
            else {
                // Do nothing
            }
        }
    }
    pthread_mutex_unlock(&lock);
}

void my_keyboard_cb(lv_event_t * e)
{
    uint32_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);

    // Find the corresponding led_t object
    led_t *led = NULL;
    for (int i = 0; i < LED_MAX_COUNT; i++) {
        if (leds[i].led == obj) {
            led = &leds[i];
            break;
        }
    }

    if (led == NULL)
        return;


    if(code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_get_act());
        switch(key) {
            case LV_KEY_UP:
                printf("LV_KEY_UP\n");
                led_move_y(led, -1);
                 break;
            case LV_KEY_DOWN:
                printf("LV_KEY_DOWN\n");
                led_move_y(led, 1);
                break;
            case LV_KEY_LEFT:
                printf("LV_KEY_LEFT\n");
                led_move_x(led, -1);
                break;
            case LV_KEY_RIGHT:
                printf("LV_KEY_RIGHT\n");
                led_move_x(led, 1);
                break;
                /* Add a case to capture when the 'R' or 'r' key is pressed */
            case 'R':
            case 'r':
                led_rotate(led);
                break;

            default:
                break;
        }
    }
}