extern "C" void application_main();

#include <cstdlib>
#include <cstring>

#include "Gpio.hpp"
#include "Serial.hpp"

static Gpio get_led0(){
#if STM32F413xx
  return Gpio(Gpio::Port::e, 4).set_output().set_value(true);
#endif
#if STM32F401xC
  return Gpio(Gpio::Port::b, 4).set_output().set_value(true);
#endif

}

static Gpio get_led1(){
#if STM32F413xx
  return Gpio(Gpio::Port::b, 9).set_output().set_value(true);
#endif
#if STM32F401xC
  return Gpio(Gpio::Port::b, 5).set_output().set_value(true);
#endif
}

void application_main(){


  constexpr uint32_t delay = !__FAST * 500 + 50;


  auto led0 = get_led0();
  auto led1 = get_led1();



  char buffer[64];
  char number[64];
  int count = 0;
  while(1){
    led0.set_value(true).wait(delay).set_value(false).wait(delay);
    led1.set_value(true).wait(delay).set_value(false).wait(delay);
    itoa(++count, number, 10);
    strncpy(buffer, "Hello World ", 63);
    strncat(buffer, number, 63);
    strncat(buffer, "\n", 63);
    Serial().write(buffer);
  }


}
