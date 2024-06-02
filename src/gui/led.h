/**
 * @file led.h
 * @author david burke
 * @brief lvgl led handler
 */

#ifndef LED_H_
#define LED_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "../lvgl/lvgl.h"

/*****************************************************************************
 * Definitions
 *****************************************************************************/

/* Maximum number of LEDs that can be registered */
#define LED_MAX_COUNT   64U

/*****************************************************************************
 * Structs, Unions, Enums, & Typedefs
 *****************************************************************************/

/**
 * @brief Enumeration of LED modes.
 */
typedef enum led_mode_t {
    LED_MODE_OFF,        /**< LED is turned off. */
    LED_MODE_ON,         /**< LED is turned on. */
    LED_MODE_FLASHING,   /**< LED is flashing. */
    LED_MODE_BREATHING,  /**< LED is breathing. */
    LED_MODE_MAX         /**< Maximum number of LED modes. */
} led_mode_t;

/**
 * @brief Structure representing an LED.
 */
typedef struct led_t {
    lv_obj_t *led;              /**< LED object returned by lv_led_create */
    lv_obj_t *parent;           /**< Window or tab that the LED will be in */
    lv_align_t align;           /**< Alignment of the LED in the window */
    int32_t x_ofs;              /**< X offset from the alignment in the window */
    int32_t y_ofs;              /**< Y offset from the alignment in the window */
    led_mode_t mode;            /**< Mode of the LED (off, on, flashing, breathing) */
    uint32_t period;            /**< Period of a flashing LED */
    float duty;                 /**< Duty of the flashing LED */
    lv_palette_t color;         /**< Color of the LED */
    uint8_t on_bright;          /**< Brightness when the LED is on */
    uint8_t off_bright;         /**< Brightness when the LED is off */
    uint8_t breath_bright;      /**< Brightness when in breathing mode */
    uint16_t breath_index;      /**< Index of the Gaussian curve */
    uint64_t on_timestamp;      /**< Used for flashing mode */
    uint64_t off_timestamp;     /**< Used for flashing mode */
    bool is_on;                 /**< Indicates if the LED is currently ON */
} led_t;

/*****************************************************************************
 * Function Prototypes
 *****************************************************************************/

/**
 * @brief Creates a new LED object.
 *
 * This function creates a new LED object and returns a pointer to it.
 *
 * @param parent The parent object to which the LED will be added.
 * @param align The alignment of the LED within its parent.
 * @param x_ofs The x offset of the LED from its parent's position.
 * @param y_ofs The y offset of the LED from its parent's position.
 * @param color The color palette to be used for the LED.
 *
 * @return A pointer to the created LED object.
 */
led_t *led_create(
    const lv_obj_t *parent,
    lv_align_t align,
    int32_t x_ofs,
    int32_t y_ofs,
    lv_palette_t color);

/**
 * @brief Sets the mode, period, and duty cycle of an LED.
 *
 * This function sets the mode, period, and duty cycle of the specified LED.
 *
 * @param led Pointer to the LED object.
 * @param mode The mode of the LED.
 * @param period The period of the LED in milliseconds.
 * @param duty The duty cycle of the LED as a percentage (0.0 - 1.0).
 */
void led_set_mode(led_t *led, led_mode_t mode, uint32_t period, float duty);

/**
 * @brief Sets the color of an LED.
 *
 * This function sets the color of the specified LED using the specified palette color.
 *
 * @param led Pointer to the LED object.
 * @param color The palette color to set for the LED.
 */
void led_set_color(led_t *led, lv_palette_t color);

/**
 * @brief Sets the brightness of an LED.
 *
 * This function sets the brightness of the specified LED for both the on and off states.
 *
 * @param led Pointer to the LED object.
 * @param on_bright The brightness level for the LED when it is on.
 * @param off_bright The brightness level for the LED when it is off.
 */
void led_set_brightness(led_t *led, uint8_t on_bright, uint8_t off_bright);

/**
 * @brief Sets the size of an LED.
 *
 * This function sets the size (width and height) of the specified LED.
 *
 * @param led Pointer to the LED object.
 * @param w The width of the LED.
 * @param h The height of the LED.
 */
void led_set_size(led_t *led, int32_t w, int32_t h);

/**
 * @brief Initializes the LED module.
 *
 * This function initializes the LED module and should be called before using any other LED functions.
 */
void led_init(void);


/**
 * @brief Processes the LED functionality.
 *
 * This function is responsible for handling the LED functionality, such as turning on/off the LED,
 * changing LED colors, and controlling LED blinking patterns.
 *
 * @note This function should be called periodically to ensure proper LED operation.
 */
void led_process(void);

/**
 * @brief Gets the position of an LED.
 *
 * This function retrieves the position of the specified LED in relation to the top left corner of the parent.
 *
 * @param led Pointer to the LED object.
 * @param pos Pointer to the position of the LED.
 *
 * @return True if the position was successfully retrieved, false otherwise.
 */
bool led_get_position(const led_t *led, lv_point_t *pos);

/**
 * @brief Moves the LED object by a specified value from its current x position.
 *
 * This function moves the LED object by the specified value from its current x position.
 *
 * @param led Pointer to the LED object.
 * @param offset The value to move the LED object by.
 *
 * @return True if the LED was successfully moved, false otherwise.
 */
bool led_move_x(led_t *led, int32_t offset);

/**
 * @brief Moves the LED object by a specified value from its current y position.
 *
 * This function moves the LED object by the specified value from its current y position.
 *
 * @param led Pointer to the LED object.
 * @param offset The value to move the LED object by.
 *
 * @return True if the LED was successfully moved, false otherwise.
 */
bool led_move_y(led_t *led, int32_t offset);

/**
 * @brief Rotates the LED object.
 *
 * This function rotates the LED object by 90 degrees.
 *
 * @param led Pointer to the LED object.
 */
void led_rotate(led_t *led);

#ifdef __cplusplus
}
#endif
#endif /* LED_H_ */