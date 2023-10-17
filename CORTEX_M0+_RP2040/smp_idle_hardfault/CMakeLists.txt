cmake_minimum_required(VERSION 3.13)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

# Pull in FreeRTOS
include(FreeRTOS_Kernel_import.cmake)

project(example C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE "Debug")

pico_sdk_init()

add_executable( smp_idle_hardfault
        main.c
        )

target_include_directories( smp_idle_hardfault PRIVATE
        ${CMAKE_CURRENT_LIST_DIR} )

target_link_libraries( smp_idle_hardfault pico_stdlib FreeRTOS-Kernel FreeRTOS-Kernel-Heap1)
pico_add_extra_outputs( smp_idle_hardfault )

# Use USB uart
pico_enable_stdio_usb( smp_idle_hardfault 1)
pico_enable_stdio_uart( smp_idle_hardfault 1)
