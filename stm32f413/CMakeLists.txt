#Copy this file to the application project folder as CMakeLists.txt
cmake_minimum_required (VERSION 3.12)

project(tboxdemo_stm32f413 CXX C ASM)

set(STM32F413_INCLUDE_DIRECTORIES
	Core/Inc
	Drivers/STM32F4xx_HAL_Driver/Inc
	Drivers/STM32F4xx_HAL_Driver/Inc/Legacy
	Drivers/CMSIS/Device/ST/STM32F4xx/Include
	Drivers/CMSIS/Include
	)

set(STM32F413_DEFINITIONS
	USE_HAL_DRIVER
	STM32F413xx
	)

set(STM32F413_CPU_OPTIONS
	-mcpu=cortex-m4
	-mthumb
	-mfpu=fpv4-sp-d16
	-mfloat-abi=hard
	)


set(STM32F413_SOURCES
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
	${CMAKE_CURRENT_SOURCE_DIR}/startup_stm32f413xx.s)

set(STM32F413_LINKER_FILE ${CMAKE_CURRENT_SOURCE_DIR}/STM32F413VGTx_FLASH.ld)

set(BLUE_TARGET ${PROJECT_NAME}_blue.elf)
set(RED_TARGET ${PROJECT_NAME}_red.elf)
set(ORANGE_TARGET ${PROJECT_NAME}_orange.elf)
set(HELLO_TARGET ${PROJECT_NAME}_hello.elf)


message(STATUS "Release Executable ${RELEASE_TARGET}")
message(STATUS "Debug Executable ${DEBUG_TARGET}")

sdk_add_base_executable(
	${BLUE_TARGET}
	"${STM32F413_SOURCES}"
	"${STM32F413_INCLUDE_DIRECTORIES}"
	"${STM32F413_CPU_OPTIONS}"
	"${STM32F413_DEFINITIONS}"
	"${STM32F413_LINKER_FILE}"
	)

target_compile_definitions(${BLUE_TARGET}
	PRIVATE
	__BLUE=1
	)

sdk_add_base_executable(
	${RED_TARGET}
	"${STM32F413_SOURCES}"
	"${STM32F413_INCLUDE_DIRECTORIES}"
	"${STM32F413_CPU_OPTIONS}"
	"${STM32F413_DEFINITIONS}"
	"${STM32F413_LINKER_FILE}"
	)

target_compile_definitions(${RED_TARGET}
	PRIVATE
	__RED=1
	)

sdk_add_base_executable(
	${ORANGE_TARGET}
	"${STM32F413_SOURCES}"
	"${STM32F413_INCLUDE_DIRECTORIES}"
	"${STM32F413_CPU_OPTIONS}"
	"${STM32F413_DEFINITIONS}"
	"${STM32F413_LINKER_FILE}"
	)

target_compile_definitions(${ORANGE_TARGET}
	PRIVATE
	__ORANGE=1
	)

sdk_add_base_executable(
	${HELLO_TARGET}
	"${STM32F413_SOURCES}"
	"${STM32F413_INCLUDE_DIRECTORIES}"
	"${STM32F413_CPU_OPTIONS}"
	"${STM32F413_DEFINITIONS}"
	"${STM32F413_LINKER_FILE}"
	)

target_compile_definitions(${HELLO_TARGET}
	PRIVATE
	__HELLO=1
	)

