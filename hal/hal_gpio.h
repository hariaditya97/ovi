#ifndef HAL_GPIO_H
#define HAL_GPIO_H

#include <stdint.h>
#include <stdbool.h>

#define HAL_PIN_ONBOARD_LED 255

/**
* @brief Logical GIP Pin States 
*/
typedef enum {
    HAL_GPIO_LOW = 0,
    HAL_GPIO_HIGH = 1
} hal_gpio_state_t;

/**
* @brief Logical GIP Pin States 
*/
typedef enum {
    HAL_GPIO_DIR_IN = 0,
    HAL_GPIO_DIR_OUT = 1
} hal_gpio_dir_t;

/** 
* @brief Special HAL Pin Definitions 
* Map virtual pins for non-standard hardware (e.g. Wi-Fi LED)
*/

/**
 * @brief Initialize a GPIO pin with direction and default state
 * 
 * @param pin Pin number (0-29 for RP2350, or HAL_PIN_ONBOARD_LED)
 * @param dir Input or Output direction
 * @return true on successful initialization, false on error
 */
bool hal_gpio_init(uint8_t pin, hal_gpio_dir_t dir);

/**
 * @brief Write a digital state (HIGH/LOW) to a GPIO pin
 * 
 * @param pin Pin number
 * @param state HAL_GPIO_HIGH or HAL_GPIO_LOW
 */
 void hal_gpio_write(uint8_t pin, hal_gpio_state_t state);

 /**
 * @brief Read the digital input state of a GPIO pin
 * 
 * @param pin Pin number
 * @return hal_gpio_state_t Current voltage state of the pin
 */
 hal_gpio_state_t hal_gpio_read(uint8_t pin);

 /**
 * @brief Configure internal pull-up / pull-down resistors
 * 
 * @param pin Pin number
 * @param pull_up true to enable pull-up, false to disable
 * @param pull_down true to enable pull-down, false to disable
 */
 void hal_gpio_set_pulls(uint8_t pin, bool pull_up, bool pull_down);
 
 #endif // HAL_GPIO_H