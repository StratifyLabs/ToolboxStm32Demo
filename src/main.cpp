extern "C" void application_main();

#include <cstdlib>
#include <cstring>

#include "Gpio.hpp"
#include "Serial.hpp"

static Gpio get_red_led(){
  return Gpio(Gpio::Port::e, 4).set_output().set_value(true);
}

static Gpio get_orange_led(){
  return Gpio(Gpio::Port::b, 9).set_output().set_value(true);
}

static Gpio get_blue_led(){
  return Gpio(Gpio::Port::e, 1).set_output().set_value(true);
}

void application_main(){
  get_red_led();
  get_orange_led();
  get_blue_led();

#if __BLUE || __HELLO
  auto active_led = get_blue_led();
#endif

#if __RED
  auto active_led = get_red_led();
#endif

#if __ORANGE
  auto active_led = get_orange_led();
#endif

  char buffer[64];
  char number[64];
  int count = 0;
  while(1){
    active_led.set_value(false).wait(1000).set_value(true).wait(500);
    itoa(++count, number, 10);
    strncpy(buffer, "Hello World ", 63);
    strncat(buffer, number, 63);
    strncat(buffer, "\n", 63);
    Serial().write(buffer);
  }


}
