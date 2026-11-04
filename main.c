#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

int main() {
    stdio_init_all();

    // Initialize CYW43 hardware (required for onboard LED on Pico 2W)
    if (cyw43_arch_init()) {
        printf("CYW43 init failed!\n");
        return -1;
    }

    printf("Ovi Pico 2W Initialized!\n");

    while (true) {
        printf("LED on!");
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(500);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        printf("LED off!");
        sleep_ms(500);
    }

    return 0;
}
