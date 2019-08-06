#ifndef CATBOXBOX_INCLUDE_BUZZER_H_
#define CATBOXBOX_INCLUDE_BUZZER_H_

#include <HID.h>

namespace catbox {

// TODO: Refactor into abstract class with virtual method for processing tone changes
enum class BuzzerPattern {
  // Constant, unchanging tone
  Tone,
  // Brief intermittent beep
  Beep,
  // Two beeps in succession
  DoubleBeep,
  // Alternating tones
  Alternating,
  // Linearly moving tone
  Linear,
  // Linearly moving tone, reversing direction when end is reached
  LinearPingPong
};

class Buzzer {
  bool enabled_ = false;
  bool loudMode_ = false;
  uint8_t pin_;
  BuzzerPattern pattern_ = BuzzerPattern::Tone;
 public:
  explicit Buzzer(uint8_t pin);
  void enable();
  void disable();
  void setLoudMode(bool enabled);
  // TODO: start()/stop()
 private:
  // TODO: process()
};

}

#endif //CATBOXBOX_INCLUDE_BUZZER_H_
