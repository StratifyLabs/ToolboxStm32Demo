#ifndef GPIO_HPP
#define GPIO_HPP

#include <stdio.h>

class Gpio {
public:

  enum class Port {
    a,b,c,d,e,f
  };

  Gpio(Port port, uint32_t pin);

  enum class Pull {
    none,
    up,
    down
  };

  Gpio & wait(uint32_t milliseconds);

  Gpio & set_input(Pull pull_value);
  Gpio & set_output();

  Gpio & set_value(bool value = true);
  bool get_value() const;

private:
  void * const m_handle = nullptr;
  const uint32_t m_pinmask;

  void * get_handle(Port port);

};

#endif // GPIO_HPP
