#ifndef CATBOXBOX_INCLUDE_SLEEPER_H_
#define CATBOXBOX_INCLUDE_SLEEPER_H_

#include <stdint-gcc.h>

namespace catbox {

// Defining INTERRUPT_COUNT based on Arduino model being used.
#if defined(ARDUINO_AVR_NANO) || defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_MINI)
  #define INTERRUPT_COUNT 2
#elif defined(ARDUINO_AVR_MICRO) || defined(ARDUINO_AVR_LEONARDO) || defined(ARDUINO_AVR_LEONARDO_ETH) || defined(ARDUINO_AVR_YUN) || defined(ARDUINO_AVR_YUNMINI)
  #define INTERRUPT_COUNT 5
#elif defined(ARDUINO_AVR_MEGA2560) || defined(ARDUINO_AVR_MEGA) || defined(ARDUINO_AVR_ADK)
  #define INTERRUPT_COUNT 6
#elif defined(AVR_UNO_WIFI_DEV_ED)
  #define INTERRUPT_COUNT 14
#else
  // Safe generic value?
  #define INT_INTERRUPT_COUNTCOUNT 16
#endif //Defining INTERRUPT_COUNT

class Sleeper {

  bool started_ = false;
  uint8_t interrupts_[INTERRUPT_COUNT] = {};

 public:
  Sleeper() = default;
  Sleeper &start();
  Sleeper &bindInterrupt(uint8_t digitalPin, void (*userFunc)(void));
  bool sleep();

 private:
  void detachInterrupts();

};

}

#endif //CATBOXBOX_INCLUDE_SLEEPER_H_
