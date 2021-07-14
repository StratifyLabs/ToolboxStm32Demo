#Copy this file to the application project folder as CMakeLists.txt
cmake_minimum_required (VERSION 3.12)

project(tboxdemo_stm32f401 CXX C ASM)

set(STM32F401_INCLUDE_DIRECTORIES
	Core/Inc
	Drivers/STM32F4xx_HAL_Driver/Inc
	Drivers/STM32F4xx_HAL_Driver/Inc/Legacy
	Drivers/CMSIS/Device/ST/STM32F4xx/Include
	Drivers/CMSIS/Include
	)

set(STM32F401_DEFINITIONS
	USE_HAL_DRIVER
	STM32F401xC
	)

set(STM32F401_CPU_OPTIONS
	-mcpu=cortex-m4
	-mthumb
	-mfpu=fpv4-sp-d16
	-mfloat-abi=hard
	)


set(STM32F401_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/../src/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../src/Gpio.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../src/Gpio.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/../src/Serial.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../src/Serial.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/main.c
	${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/stm32f4xx_it.c
	${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/stm32f4xx_hal_msp.c
	${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c
	${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c
	${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c
	${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c
	${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c
	${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c
	${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c
	${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c
	${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c
	${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c
	${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c
	${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c
	${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c
	${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c
	${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c
	${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c
	${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/system_stm32f4xx.c
	${CMAKE_CURRENT_SOURCE_DIR}/startup_stm32f401xc.s)

set(STM32F401_LINKER_FILE ${CMAKE_CURRENT_SOURCE_DIR}/STM32F401CCUx_FLASH.ld)

set(FAST_TARGET ${PROJECT_NAME}_fast.elf)
set(SLOW_TARGET ${PROJECT_NAME}_slow.elf)


message(STATUS "Release Executable ${RELEASE_TARGET}")
message(STATUS "Debug Executable ${DEBUG_TARGET}")

sdk_add_base_executable(
	${FAST_TARGET}
	"${STM32F401_SOURCES}"
	"${STM32F401_INCLUDE_DIRECTORIES}"
	"${STM32F401_CPU_OPTIONS}"
	"${STM32F401_DEFINITIONS}"
	"${STM32F401_LINKER_FILE}"
	)

target_compile_definitions(${FAST_TARGET}
	PRIVATE
	__FAST=1
	)

sdk_add_base_executable(
	${SLOW_TARGET}
	"${STM32F401_SOURCES}"
	"${STM32F401_INCLUDE_DIRECTORIES}"
	"${STM32F401_CPU_OPTIONS}"
	"${STM32F401_DEFINITIONS}"
	"${STM32F401_LINKER_FILE}"
	)

target_compile_definitions(${SLOW_TARGET}
	PRIVATE
	__FAST=0
	)
