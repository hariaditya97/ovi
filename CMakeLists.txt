cmake_minimum_required(VERSION 3.13)

# Target the Pico 2W board specifically
set(PICO_BOARD pico2_w)

include(pico_sdk_import.cmake)

project(ovi C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(ovi
    main.c
)

# Link standard SDK + CYW43 driver for onboard LED
target_link_libraries(ovi
    pico_stdlib
    pico_cyw43_arch_none
)

pico_enable_stdio_usb(ovi 1)
pico_enable_stdio_uart(ovi 0)

pico_add_extra_outputs(ovi)
