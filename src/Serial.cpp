#include <cstring>

#include "Serial.hpp"

#include "stm32f4xx.h"

extern "C" UART_HandleTypeDef huart10;


Serial::Serial()
{

}


Serial & Serial::write(const char * message){
  size_t length = strnlen(message, 64);
  HAL_UART_Transmit(&huart10, (uint8_t*)message, length, HAL_MAX_DELAY);
  return *this;
}
