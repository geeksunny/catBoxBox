#include "Sleeper.h"

#include <avr/sleep.h>
#include <HID.h>

namespace catbox {

Sleeper &Sleeper::start() {
  if (!started_) {
    started_ = true;
    sleep_enable();
  }
  return *this;
}

Sleeper &Sleeper::bindInterrupt(uint8_t digitalPin, void (*userFunc)(void)) {
  if (started_) {
    uint8_t interruptPin = digitalPinToInterrupt(digitalPin);
    if (interruptPin != NOT_AN_INTERRUPT) {
      attachInterrupt(interruptPin, userFunc, LOW);
      interrupts_[interruptPin] = 1;
    }
    // TODO: Error reporting for NOT_AN_INTERRUPT ?
  }
  return *this;
}

bool Sleeper::sleep() {
  if (!started_) {
    return false;
  }
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_cpu();
  // Device wake-up
  sleep_disable();
  detachInterrupts();
  started_ = false;
  return true;
}

void Sleeper::detachInterrupts() {
  for (int i = 0; i < INTERRUPT_COUNT; ++i) {
    if (interrupts_[i]) {
      detachInterrupt(i);
      interrupts_[i] = 0;
    }
  }
}

}