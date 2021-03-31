#include "Gpio.hpp"

#include "stm32f4xx.h"

Gpio::Gpio(Port port_value, uint32_t pin)
    : m_handle(get_handle(port_value)), m_pinmask(1 << pin) {}

void *Gpio::get_handle(Port port) {
  switch (port) {
  case Port::a:
    return GPIOA;
  case Port::b:
    return GPIOB;
  case Port::c:
    return GPIOC;
  case Port::d:
    return GPIOD;
  case Port::e:
    return GPIOE;
  case Port::f:
    return GPIOF;
  }
  // assert
  return nullptr;
}

Gpio & Gpio::wait(uint32_t milliseconds){
  HAL_Delay(milliseconds);
  return *this;
}

Gpio &Gpio::set_input(Pull pull_value) {
  GPIO_TypeDef *handle = reinterpret_cast<GPIO_TypeDef *>(m_handle);

  GPIO_InitTypeDef GPIO_InitStruct{};
  GPIO_InitStruct.Pin = m_pinmask;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;

  GPIO_InitStruct.Pull = [](Pull value) {
    switch (value) {
    case Pull::none:
      return GPIO_NOPULL;
    case Pull::up:
      return GPIO_PULLUP;
    case Pull::down:
      return GPIO_PULLDOWN;
    }
    return GPIO_NOPULL;
  }(pull_value);

  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(handle, &GPIO_InitStruct);
  return *this;
}

Gpio &Gpio::set_output() {
  GPIO_TypeDef *handle = reinterpret_cast<GPIO_TypeDef *>(m_handle);

  GPIO_InitTypeDef GPIO_InitStruct{};
  GPIO_InitStruct.Pin = m_pinmask;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(handle, &GPIO_InitStruct);
  return *this;
}

Gpio &Gpio::set_value(bool value) {
  GPIO_TypeDef *handle = reinterpret_cast<GPIO_TypeDef *>(m_handle);
  HAL_GPIO_WritePin(handle, m_pinmask, value ? GPIO_PIN_SET : GPIO_PIN_RESET);
  return *this;
}

bool Gpio::get_value() const {
  GPIO_TypeDef *handle = reinterpret_cast<GPIO_TypeDef *>(m_handle);
  return HAL_GPIO_ReadPin(handle, m_pinmask) == GPIO_PIN_SET;
}
