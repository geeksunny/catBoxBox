#ifndef CATBOXBOX_INCLUDE_CATBOX_H_
#define CATBOXBOX_INCLUDE_CATBOX_H_

#include "Buzzer.h"
#include "Clock.h"
#include "ShiftRegister.hpp"
#include "Sleeper.h"

namespace catbox {

class Catbox {

  uint8_t timeout_ = 0;
  bool timeSetMode_ = false;

  Buzzer buzzer_;
  Clock clock_;
  Input74HC165<8> dipSwitches_;
  Sleeper sleeper_;

 public:
  Catbox();
  void setup();
  void loop();
  void playTest();

 private:
  void readDipSwitches();
  void timeSetLoop();

};

}

#endif //CATBOXBOX_INCLUDE_CATBOX_H_
