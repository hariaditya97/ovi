#include <stdio.h>
#include "pico/stdlib.h"
#include "./hal/hal_gpio.h"

int main() {
    stdio_init_all();

    // Initialize onboard LED using portable HAL
    if (!hal_gpio_init(HAL_PIN_ONBOARD_LED, HAL_GPIO_DIR_OUT)) {
        printf("HAL GPIO Init Failed!\n");
        return -1;
    }
        
    printf("Ovi HAL Abstraction Active!\n");

    uint32_t counter = 0;

    while (true) {

        // Toggle onboard LED using HAL
        printf("LED ON!");
        hal_gpio_write(HAL_PIN_ONBOARD_LED, HAL_GPIO_HIGH);
        printf("[Tick %lu] Ovi Status: Awake & Breathing (HAL LED ON)\n", counter++);
        sleep_ms(500);
        
        printf("LED OFF");
        hal_gpio_write(HAL_PIN_ONBOARD_LED, HAL_GPIO_LOW);
        sleep_ms(500);
    }

    return 0;
}