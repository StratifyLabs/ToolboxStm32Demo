#Copy this file to the application project folder as CMakeLists.txt
cmake_minimum_required (VERSION 3.12)

if(NOT SDK_PATH)
	set(SDK_PATH $ENV{TBOXDEMO_SDK_PATH})
endif()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/toolchain.cmake)

project(tboxdemo CXX C ASM)

include(sdk)

add_subdirectory(stm32f413 stm32f413)
add_subdirectory(stm32f401 stm32f401)
