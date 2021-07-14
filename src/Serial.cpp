#include <cstring>

#include "Serial.hpp"

#include "stm32f4xx.h"

#if STM32F401xC
extern "C" UART_HandleTypeDef huart1;
#define UART_HANDLE &huart1
#endif

#if STM32F413xx
extern "C" UART_HandleTypeDef huart10;
#define UART_HANDLE &huart10
#endif


Serial::Serial()
{

}


Serial & Serial::write(const char * message){
  size_t length = strnlen(message, 64);
  HAL_UART_Transmit(UART_HANDLE, (uint8_t*)message, length, HAL_MAX_DELAY);
  return *this;
}
