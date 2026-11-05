#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "power_state_machine.h"

void print_character_status(power_state_t state, const sensor_data_t *sensors) {
    printf("\n=== MOCK SENSOR INPUTS ===\n");
    printf("Battery: %.2fV | Lux: %.1f lx | Temp: %.1f C | Motion: %s\n",
          sensors->battery_voltage, sensors->lux, sensors->temp_c,
          sensors->motion_detected ? "YES" : "NO");  
          
    printf("=== OVI CHARACTER REACTION ===\n");
    switch (state) {
        case STATE_AWAKE_ACTIVE:
            printf("Display : [ (O w O) ] (Wide awake & energetic!)\n");
            printf("Tail PWM: Fast Happy Wag (1500us -> 2000us)\n");
            break;
        case STATE_AWAKE_IDLE:
            printf("Display : [ (- w -) ] (Calm & observing...)\n");
            printf("Tail PWM: Slow Micro-Twitch\n");
            break;
        case STATE_SLEEPY_LOW_BATTERY:
            printf("Display : [ (u _ u) ] (Low Battery... feeling sleepy)\n");
            printf("Tail PWM: Disabled (0us - Power Gated)\n");
            break;
        case STATE_DEEP_SLEEP:
            printf("Display : [ ( - - ) ] (Zzz... Pitch dark / Pocket mode)\n");
            printf("Tail PWM: Disabled (0us - Power Gated)\n");
            break;
    }
    printf("----------------------------------------\n");
}

int main (void) {
    power_state_init();

    // Simulated Sensor Sequences Over Time
    sensor_data_t test_scenarios[] = {
        { .battery_voltage = 3.9f, .lux = 250.0f, .temp_c = 22.0f, .motion_detected = true  }, // Day walk
        { .battery_voltage = 3.8f, .lux = 5.0f,   .temp_c = 21.0f, .motion_detected = false }, // Dim room
        { .battery_voltage = 3.7f, .lux = 0.2f,   .temp_c = 19.0f, .motion_detected = false }, // Pocket / Dark
        { .battery_voltage = 3.3f, .lux = 150.0f, .temp_c = 22.0f, .motion_detected = true  }  // Low battery trip
    };

    size_t num_tests = sizeof(test_scenarios) / sizeof(test_scenarios[0]);

    for (size_t i = 0; i < num_tests; i++) {
        power_state_t state = power_state_update(&test_scenarios[i]);
        print_character_status(state, &test_scenarios[i]);
        sleep(1); // 1-second delay between ticks on Mac
    }

    return 0;
}