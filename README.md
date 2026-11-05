# Ovi — Offline Ambient Digital Charm

Ovi is an offline-first, ambient physical digital companion built on the Raspberry Pi Pico 2W (RP2350). It uses environment sensing and micro-actuation to express character.

---

## Tech Stack [Prototype Only]

* **MCU:** Raspberry Pi Pico 2W (RP2350, ARM Cortex-M33)
* **Toolchain:** Pico SDK v2.3.1, C11, CMake, ARM GNU Toolchain
* **Architecture:** Hardware Abstraction Layer (HAL) for MCU portability
* **Testing:** Offline macOS C desktop simulator 

---

## Milestone Progress

- [x] **Toolchain & USB Serial Bring-Up:** Target compilation for RP2350 Cortex-M33, `pico2_w` SDK setup, and live USB serial logging 
- [x] **HAL GPIO Layer:** Implemented `hal_gpio.h` and `hal_gpio_pico.c` to wrap onboard CYW43 LED/GPIO logic cleanly
- [x] **Mac Desktop Simulator:** Host CLI binary (`ovi_sim`) to test state machine transitions offline using native GCC
- [x] **State Machine Integration:** Ported `power_state_machine.c` into `src/main.c` running live telemetry on target   silicon
- [ ] **I2C Sensor Bus (`hal_i2c`):** Bus scanner and drivers for BMA400 IMU tap interrupts and VEML7700 light sensing
- [ ] **Actuation & Power Gating:** 50 Hz PWM tail servo control with high-side P-FET power isolation

---

## 📂 Project Layout

```text
ovi/
├── CMakeLists.txt         # Pico 2W CMake build configuration
├── app/                   # Portable state machine & behavior logic
├── hal/                   # Hardware abstraction interfaces & Pico drivers
├── sim/                   # macOS desktop simulator (ovi_sim)
└── src/                   # Main target entry point (main.c)
