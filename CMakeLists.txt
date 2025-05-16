cmake_minimum_required(VERSION 3.22)

# Setup compiler settings
set(CMAKE_C_STANDARD            11)
set(CMAKE_C_STANDARD_REQUIRED   ON)
set(CMAKE_C_EXTENSIONS          ON)

# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()
message("Build type: " ${CMAKE_BUILD_TYPE})

# Set paths
set(CORE_DIR            ${CMAKE_SOURCE_DIR}/core)
set(BSP_DIR             ${CMAKE_SOURCE_DIR}/STM32CubeF7/Drivers/BSP)
set(HAL_DIR             ${CMAKE_SOURCE_DIR}/STM32CubeF7/Drivers/STM32F7xx_HAL_Driver)
set(LVGL_DIR            ${CMAKE_SOURCE_DIR}/lvgl)
set(LVGL_HAL_DIR        ${CMAKE_SOURCE_DIR}/lvgl_hal)
set(CMAKE_DIR           ${CMAKE_SOURCE_DIR}/cmake)
set(CMSIS_DIR           ${CMAKE_SOURCE_DIR}/STM32CubeF7/Drivers/CMSIS)

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Set linker script
set(STM32_LINKER_SCRIPT "core/LinkerScript.ld")

## Include toolchain file
include("${CMAKE_DIR}/gcc-arm-none-eabi.cmake")

# Set the project name
set(CMAKE_PROJECT_NAME STM32F769_LVGL)
project(${CMAKE_PROJECT_NAME})

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# In order to use CMake for cross-compiling
set(CMAKE_CXX_COMPILER_FORCED "true") 

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    DEBUG
    USE_HAL_DRIVER
    STM32F769xx
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${BSP_DIR}/STM32F769i-Discovery
    ${CMAKE_SOURCE_DIR}
    ${CMSIS_DIR}/Include
    ${CMSIS_DIR}/Core/Include
    ${CMSIS_DIR}/Device/ST/STM32F7xx/Include
    ${CORE_DIR}/inc
    ${HAL_DIR}/Inc
    ${LVGL_DIR}
    ${LVGL_HAL_DIR}
)

# Add compiler specific sources
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    ${CORE_DIR}/startup_stm32f769xx.s
    ${CORE_DIR}/src/syscalls.c
)

# Core
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    ${CORE_DIR}/src/main.c
    ${CORE_DIR}/src/stm32f7xx_it.c
    ${CORE_DIR}/src/system_stm32f7xx.c
)

# HAL
file(GLOB_RECURSE HAL_SOURCES "${HAL_DIR}/Src/*.c")
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    ${HAL_DIR}/Src/stm32f7xx_hal.c
    ${HAL_DIR}/Src/stm32f7xx_hal_adc.c
    ${HAL_DIR}/Src/stm32f7xx_hal_adc_ex.c
    ${HAL_DIR}/Src/stm32f7xx_hal_can.c
    ${HAL_DIR}/Src/stm32f7xx_hal_cec.c
    ${HAL_DIR}/Src/stm32f7xx_hal_cortex.c
    ${HAL_DIR}/Src/stm32f7xx_hal_crc.c
    ${HAL_DIR}/Src/stm32f7xx_hal_crc_ex.c
    ${HAL_DIR}/Src/stm32f7xx_hal_cryp.c
    ${HAL_DIR}/Src/stm32f7xx_hal_cryp_ex.c
    ${HAL_DIR}/Src/stm32f7xx_hal_dac.c
    ${HAL_DIR}/Src/stm32f7xx_hal_dac_ex.c
    ${HAL_DIR}/Src/stm32f7xx_hal_dcmi.c
    ${HAL_DIR}/Src/stm32f7xx_hal_dcmi_ex.c
    ${HAL_DIR}/Src/stm32f7xx_hal_dfsdm.c
    ${HAL_DIR}/Src/stm32f7xx_hal_dma.c
    ${HAL_DIR}/Src/stm32f7xx_hal_dma2d.c
    ${HAL_DIR}/Src/stm32f7xx_hal_dma_ex.c
    ${HAL_DIR}/Src/stm32f7xx_hal_dsi.c
    ${HAL_DIR}/Src/stm32f7xx_hal_eth.c
    ${HAL_DIR}/Src/stm32f7xx_hal_exti.c
    ${HAL_DIR}/Src/stm32f7xx_hal_flash.c
    ${HAL_DIR}/Src/stm32f7xx_hal_flash_ex.c
    ${HAL_DIR}/Src/stm32f7xx_hal_gpio.c
    ${HAL_DIR}/Src/stm32f7xx_hal_hash.c
    ${HAL_DIR}/Src/stm32f7xx_hal_hash_ex.c
    ${HAL_DIR}/Src/stm32f7xx_hal_hcd.c
    ${HAL_DIR}/Src/stm32f7xx_hal_i2c.c
    ${HAL_DIR}/Src/stm32f7xx_hal_i2c_ex.c
    ${HAL_DIR}/Src/stm32f7xx_hal_i2s.c
    ${HAL_DIR}/Src/stm32f7xx_hal_irda.c
    ${HAL_DIR}/Src/stm32f7xx_hal_iwdg.c
    ${HAL_DIR}/Src/stm32f7xx_hal_jpeg.c
    ${HAL_DIR}/Src/stm32f7xx_hal_lptim.c
    ${HAL_DIR}/Src/stm32f7xx_hal_ltdc.c
    ${HAL_DIR}/Src/stm32f7xx_hal_ltdc_ex.c
    ${HAL_DIR}/Src/stm32f7xx_hal_mdios.c
    ${HAL_DIR}/Src/stm32f7xx_hal_mmc.c
    ${HAL_DIR}/Src/stm32f7xx_hal_nand.c
    ${HAL_DIR}/Src/stm32f7xx_hal_nor.c
    ${HAL_DIR}/Src/stm32f7xx_hal_pcd.c
    ${HAL_DIR}/Src/stm32f7xx_hal_pcd_ex.c
    ${HAL_DIR}/Src/stm32f7xx_hal_pwr.c
    ${HAL_DIR}/Src/stm32f7xx_hal_pwr_ex.c
    ${HAL_DIR}/Src/stm32f7xx_hal_qspi.c
    ${HAL_DIR}/Src/stm32f7xx_hal_rcc.c
    ${HAL_DIR}/Src/stm32f7xx_hal_rcc_ex.c
    ${HAL_DIR}/Src/stm32f7xx_hal_rng.c
    ${HAL_DIR}/Src/stm32f7xx_hal_rtc.c
    ${HAL_DIR}/Src/stm32f7xx_hal_rtc_ex.c
    ${HAL_DIR}/Src/stm32f7xx_hal_sai.c
    ${HAL_DIR}/Src/stm32f7xx_hal_sai_ex.c
    ${HAL_DIR}/Src/stm32f7xx_hal_sd.c
    ${HAL_DIR}/Src/stm32f7xx_hal_sdram.c
    ${HAL_DIR}/Src/stm32f7xx_hal_smartcard.c
    ${HAL_DIR}/Src/stm32f7xx_hal_smartcard_ex.c
    ${HAL_DIR}/Src/stm32f7xx_hal_smbus.c
    ${HAL_DIR}/Src/stm32f7xx_hal_spdifrx.c
    ${HAL_DIR}/Src/stm32f7xx_hal_spi.c
    ${HAL_DIR}/Src/stm32f7xx_hal_spi_ex.c
    ${HAL_DIR}/Src/stm32f7xx_hal_sram.c
    ${HAL_DIR}/Src/stm32f7xx_hal_tim.c
    ${HAL_DIR}/Src/stm32f7xx_hal_tim_ex.c
    ${HAL_DIR}/Src/stm32f7xx_hal_uart.c
    ${HAL_DIR}/Src/stm32f7xx_hal_uart_ex.c
    ${HAL_DIR}/Src/stm32f7xx_hal_usart.c
    ${HAL_DIR}/Src/stm32f7xx_hal_wwdg.c
    ${HAL_DIR}/Src/stm32f7xx_ll_adc.c
    ${HAL_DIR}/Src/stm32f7xx_ll_crc.c
    ${HAL_DIR}/Src/stm32f7xx_ll_dac.c
    ${HAL_DIR}/Src/stm32f7xx_ll_dma.c
    ${HAL_DIR}/Src/stm32f7xx_ll_dma2d.c
    ${HAL_DIR}/Src/stm32f7xx_ll_exti.c
    ${HAL_DIR}/Src/stm32f7xx_ll_fmc.c
    ${HAL_DIR}/Src/stm32f7xx_ll_gpio.c
    ${HAL_DIR}/Src/stm32f7xx_ll_i2c.c
    ${HAL_DIR}/Src/stm32f7xx_ll_lptim.c
    ${HAL_DIR}/Src/stm32f7xx_ll_pwr.c
    ${HAL_DIR}/Src/stm32f7xx_ll_rcc.c
    ${HAL_DIR}/Src/stm32f7xx_ll_rng.c
    ${HAL_DIR}/Src/stm32f7xx_ll_rtc.c
    ${HAL_DIR}/Src/stm32f7xx_ll_sdmmc.c
    ${HAL_DIR}/Src/stm32f7xx_ll_spi.c
    ${HAL_DIR}/Src/stm32f7xx_ll_tim.c
    ${HAL_DIR}/Src/stm32f7xx_ll_usart.c
    ${HAL_DIR}/Src/stm32f7xx_ll_usb.c
    ${HAL_DIR}/Src/stm32f7xx_ll_utils.c
)

# BSP
file(GLOB_RECURSE BSP_SOURCES "${BSP_DIR}/STM32F769i-Discovery/*.c")
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    ${BSP_SOURCES}
)

# BSP Components
file(GLOB_RECURSE BSP_COMPONENTS_SOURCES "${BSP_DIR}/Components/*.c")
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    ${BSP_COMPONENTS_SOURCES}
)

# LVGL HAL
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    ${LVGL_HAL_DIR}/tft/tft.c
    ${LVGL_HAL_DIR}/touchpad/touchpad.c
)

# LVGL core sources
file(GLOB_RECURSE LVGL_SOURCES "${LVGL_DIR}/src/*.c")
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    ${LVGL_SOURCES}
)

file(GLOB_RECURSE EXAMPLES_SOURCES "${LVGL_DIR}/demos/widgets/*.c")
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    ${EXAMPLES_SOURCES}
)

# Validate that STM32CubeMX code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()
