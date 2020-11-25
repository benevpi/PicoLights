cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(picolights)

pico_sdk_init()

add_executable(picolights)

pico_generate_pio_header(picolights ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio)

target_sources(picolights PRIVATE picolights.c)

target_link_libraries(picolights PRIVATE pico_stdlib hardware_pio)
pico_add_extra_outputs(picolights)

