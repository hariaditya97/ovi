#include "power_state_machine.h"

static power_state_t current_state = STATE_AWAKE_IDLE; 

void power_state_init(void) {
    current_state = STATE_AWAKE_ACTIVE;
}

power_state_t power_state_update(const sensor_data_t *inputs) {
    // Priority 1: Critical low battery check (<3.4V threshold)
    if (inputs->battery_voltage < 3.4f) {
        current_state = STATE_SLEEPY_LOW_BATTERY;
        return current_state;
    }

    // Priority 2: Environmental sleep condition (Pitch dark pocket/room)
    if (inputs->lux < 1.0f && !inputs->motion_detected) {
        current_state = STATE_DEEP_SLEEP;
        return current_state;
    }

    // Priority 3: Active vs Idle transitions based on movement or light
    if (inputs->motion_detected || inputs->lux > 10.0f) {
        current_state = STATE_AWAKE_ACTIVE;
    } else {
        current_state = STATE_AWAKE_IDLE;
    }

    return current_state;
}
