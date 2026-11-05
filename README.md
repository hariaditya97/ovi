# 🐾 Ovi — Offline Robotic Bag Charm

Ovi is an offline-first, physical digital companion built on the Raspberry Pi Pico 2W (RP2350)[span_4](start_span)[span_4](end_span)[span_5](start_span)[span_5](end_span). It uses environment sensing and micro-actuation to express character without screens, apps, or cloud tracking[span_6](start_span)[span_6](end_span)[span_7](start_span)[span_7](end_span).

---

## 🛠 Tech Stack

* **MCU:** Raspberry Pi Pico 2W (RP2350, ARM Cortex-M33)[span_8](start_span)[span_8](end_span)[span_9](start_span)[span_9](end_span)
* **Toolchain:** Pico SDK v2.3.1, C11, CMake, ARM GNU Toolchain[span_10](start_span)[span_10](end_span)[span_11](start_span)[span_11](end_span)
* **Architecture:** Hardware Abstraction Layer (HAL) for MCU portability[span_12](start_span)[span_12](end_span)[span_13](start_span)[span_13](end_span)
* **Testing:** Offline macOS C desktop simulator (`sim/ovi_sim`)[span_14](start_span)[span_14](end_span)[span_15](start_span)[span_15](end_span)

---

## 🎯 Milestone Progress

- [x] **Toolchain & USB Serial Bring-Up:** Target compilation for RP2350 Cortex-M33, `pico2_w` SDK setup, and live USB serial logging (`115200` baud)[span_16](start_span)[span_16](end_span)[span_17](start_span)[span_17](end_span).
- [x] **HAL GPIO Layer:** Implemented `hal_gpio.h` and `hal_gpio_pico.c` to wrap onboard CYW43 LED/GPIO logic cleanly[span_18](start_span)[span_18](end_span)[span_19](start_span)[span_19](end_span).
- [x] **Mac Desktop Simulator:** Host CLI binary (`ovi_sim`) to test state machine transitions offline using native GCC[span_20](start_span)[span_20](end_span)[span_21](start_span)[span_21](end_span).
- [x] **State Machine Integration:** Ported `power_state_machine.c` into `src/main.c` running live telemetry on target silicon[span_22](start_span)[span_22](end_span)[span_23](start_span)[span_23](end_span).
- [ ] **I2C Sensor Bus (`hal_i2c`):** Bus scanner and drivers for BMA400 IMU tap interrupts and VEML7700 light sensing[span_24](start_span)[span_24](end_span)[span_25](start_span)[span_25](end_span).
- [ ] **Actuation & Power Gating:** 50 Hz PWM tail servo control with high-side P-FET power isolation[span_26](start_span)[span_26](end_span)[span_27](start_span)[span_27](end_span).

---

## 📂 Project Layout

```text
ovi/
├── CMakeLists.txt         # Pico 2W CMake build configuration
├── app/                   # Portable state machine & behavior logic
├── hal/                   # Hardware abstraction interfaces & Pico drivers
├── sim/                   # macOS desktop simulator (ovi_sim)
└── src/                   # Main target entry point (main.c)
