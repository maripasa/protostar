cmake_minimum_required(VERSION 3.13...3.27)
include(lib/pico-sdk/pico_sdk_init.cmake)
project(protostar)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(protostar
    src/display.c
    lib/display/draw.c
    lib/display/ssd1306_i2c.c
)

target_link_libraries(protostar
    pico_stdlib
    hardware_i2c
)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(protostar)
