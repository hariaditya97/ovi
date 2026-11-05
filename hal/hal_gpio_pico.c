#include "hal_gpio.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

// Track if CYW43 Wi-Fi architecture driver has been initialised.
static bool cyw43_initialised = false; 

bool hal_gpio_init(uint8_t pin, hal_gpio_dir_t dir) {

    // Handle the Pico 2W onboard LED mapped to the CYW43 Wi-Fi chip
    if (pin == HAL_PIN_ONBOARD_LED) {
      if (!cyw43_initialised) {
        if (cyw43_arch_init() == 0) {
            cyw43_initialised = true;
            return true;
        } 
        return false;
      } 
    return true;
    }

    // Standard RP2350 GPIO Pin initialization
    if (pin < NUM_BANK0_GPIOS) {
        gpio_init(pin);
        gpio_set_dir(pin, (dir == HAL_GPIO_DIR_OUT) ? GPIO_OUT : GPIO_IN);
        return true;
    }
    return false; 
} 

void hal_gpio_write(uint8_t pin, hal_gpio_state_t state) {
    
    // Light up onboard LED
    if (pin == HAL_PIN_ONBOARD_LED) {
        if (cyw43_initialised) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, state == HAL_GPIO_HIGH ? 1 : 0);  
        }
        return; 
    }

    if (pin < NUM_BANK0_GPIOS) {
        gpio_put(pin, state == HAL_GPIO_HIGH ? 1 : 0);
    }
}

hal_gpio_state_t hal_gpio_read(uint8_t pin) {
    
    if (pin == HAL_PIN_ONBOARD_LED) {
        if (cyw43_initialised) {
            bool val = cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN);
            return val ? HAL_GPIO_HIGH : HAL_GPIO_LOW;
        }
    }

    if (pin < NUM_BANK0_GPIOS) {
        return gpio_get(pin) ? HAL_GPIO_HIGH : HAL_GPIO_LOW;
    }
    return HAL_GPIO_LOW;
}

void hal_gpio_set_pulls(uint8_t pin, bool pull_up, bool pull_down) {
    if (pin < NUM_BANK0_GPIOS) {
        gpio_set_pulls(pin, pull_up, pull_down);
    }
}