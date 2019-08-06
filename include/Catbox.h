#ifndef CATBOXBOX_INCLUDE_CATBOX_H_
#define CATBOXBOX_INCLUDE_CATBOX_H_

#include "ShiftRegister.hpp"
#include "Clock.h"
#include "Sleeper.h"

#define LED_ON(Pin)           digitalWrite(Pin, HIGH)
#define LED_OFF(Pin)          digitalWrite(Pin, LOW)
#define IS_INPUT_ACTIVE(Pin)  (digitalRead(Pin) == LOW)

// Input
#define PIN_BTN_RESET_TIMER     12
#define PIN_DIP_TIME_SET_MODE   7
// Output
#define PIN_BUZZER              10
// PWM Output
#define PIN_LED_GRN             11
#define PIN_LED_YLW             9
#define PIN_LED_RED             6
// 74HC165 I/O
#define PIN_74HC165_DATA        2 // IC-PIN-9, "SO" Serial-Output
#define PIN_74HC165_CLK         4 // IC-PIN-2, Clock
#define PIN_74HC165_LATCH       3 // IC-PIN-1, Shift / Load

// TODO : Define interrupt pins to be used...
//  Nano's interrupts: 2, 3

namespace catbox {

class Buzzer {
  bool enabled_ = false;
  bool loudMode_ = false;
  uint8_t pin_;
 public:
  Buzzer(uint8_t pin);
  void enable();
  void disable();
  void setLoudMode(bool enabled);
 private:
};

class Catbox {

  uint8_t timeout_ = 0;
  bool timeSetMode_ = false;

  Buzzer buzzer_ = Buzzer(PIN_BUZZER);
  Clock clock_;
  Input74HC165<8> dipSwitches_ = Input74HC165<8>(PIN_74HC165_DATA, PIN_74HC165_CLK, PIN_74HC165_LATCH);
  Sleeper sleeper_;

 public:
  Catbox() = default;
  void setup();
  void loop();
  void playTest();

 private:
  void readDipSwitches();
  void timeSetLoop();

};

}

#endif //CATBOXBOX_INCLUDE_CATBOX_H_
