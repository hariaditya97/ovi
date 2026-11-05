#ifndef POWER_STATE_MACHINE_H
#define POWER_STATE_MACHINE_H

#include <stdbool.h>
#include <stdint.h>

/** 
* @brief Core Power and Mood States
*/
typedef enum {
    STATE_BOOTING_UP,
    STATE_AWAKE_IDLE,
    STATE_AWAKE_ACTIVE,
    STATE_SLEEPY_LOW_BATTERY,
    STATE_DEEP_SLEEP
} power_state_t; 

/**
 * @brief Unified Sensor Input Data Contract
 */
typedef struct {
    float battery_voltage;
    float lux;
    float temp_c;
    bool motion_detected;
} sensor_data_t;

/**
 * @brief Initialize Power & State Machine
 */
void power_state_init(void);

/**
 * @brief Evaluates current sensor inputs and returns the new power state
 * 
 * @param inputs Pointer to current sensor readings
 * @return power_state_t The updated system state
 */
power_state_t power_state_update(const sensor_data_t *inputs);

#endif // POWER_STATE_MACHINE_H
