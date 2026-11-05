#include <stdio.h>
#include "pico/stdlib.h"
#include "hal/hal_gpio.h"
#include "app/power_state_machine.h"

int main() {
    // 1. Initialize USB CDC serial output
    stdio_init_all();

    // 2. Initialize onboard LED via portable HAL
    if (!hal_gpio_init(HAL_PIN_ONBOARD_LED, HAL_GPIO_DIR_OUT)) {
        printf("HAL GPIO Init Failed!\n");
        return -1;
    }

    // 3. Initialize Ovi's power state machine engine
    power_state_init();
    printf("Ovi State Machine Integrated on RP2350 Pico 2W!\n");

    // Sample telemetry sequences to cycle through on target silicon
    sensor_data_t test_telemetry[] = {
        { .battery_voltage = 3.9f, .lux = 250.0f, .temp_c = 22.0f, .motion_detected = true  }, // Awake Active
        { .battery_voltage = 3.8f, .lux = 5.0f,   .temp_c = 21.0f, .motion_detected = false }, // Awake Idle
        { .battery_voltage = 3.7f, .lux = 0.2f,   .temp_c = 19.0f, .motion_detected = false }, // Deep Sleep Mode
        { .battery_voltage = 3.3f, .lux = 150.0f, .temp_c = 22.0f, .motion_detected = true  }  // Low Battery Trip
    };

    uint32_t step = 0;
    size_t total_steps = sizeof(test_telemetry) / sizeof(test_telemetry[0]);

    while (true) {
        // Fetch current simulated telemetry step
        sensor_data_t *current_readings = &test_telemetry[step % total_steps];

        // Process readings through state machine engine
        power_state_t state = power_state_update(current_readings);

        // Control physical LED output and log state updates based on machine state
        switch (state) {
            case STATE_AWAKE_ACTIVE:
                hal_gpio_write(HAL_PIN_ONBOARD_LED, HAL_GPIO_HIGH);
                printf("[Step %lu] State: AWAKE_ACTIVE | Batt: %.2fV | Lux: %.1f | LED: ON\n",
                       step, current_readings->battery_voltage, current_readings->lux);
                break;

            case STATE_AWAKE_IDLE:
                hal_gpio_write(HAL_PIN_ONBOARD_LED, HAL_GPIO_HIGH);
                printf("[Step %lu] State: AWAKE_IDLE   | Batt: %.2fV | Lux: %.1f | LED: ON\n",
                       step, current_readings->battery_voltage, current_readings->lux);
                break;

            case STATE_SLEEPY_LOW_BATTERY:
                hal_gpio_write(HAL_PIN_ONBOARD_LED, HAL_GPIO_LOW);
                printf("[Step %lu] State: LOW_BATTERY  | Batt: %.2fV | Lux: %.1f | LED: OFF\n",
                       step, current_readings->battery_voltage, current_readings->lux);
                break;

            case STATE_DEEP_SLEEP:
                hal_gpio_write(HAL_PIN_ONBOARD_LED, HAL_GPIO_LOW);
                printf("[Step %lu] State: DEEP_SLEEP   | Batt: %.2fV | Lux: %.1f | LED: OFF\n",
                       step, current_readings->battery_voltage, current_readings->lux);
                break;
        }

        step++;
        sleep_ms(2000); // 2-second interval between telemetry evaluations
    }

    return 0;
}
