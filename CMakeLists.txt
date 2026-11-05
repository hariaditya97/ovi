cmake_minimum_required(VERSION 3.13)

set(PICO_BOARD pico2_w)

include(pico_sdk_import.cmake)

project(ovi C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

# Add include directories so headers in hal/ and app/ can be referenced cleanly
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(ovi
    src/main.c
    hal/hal_gpio_pico.c
    app/power_state_machine.c
)

target_link_libraries(ovi
    pico_stdlib
    pico_cyw43_arch_none
)

pico_enable_stdio_usb(ovi 1)
pico_enable_stdio_uart(ovi 0)

pico_add_extra_outputs(ovi)
