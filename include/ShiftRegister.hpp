#ifndef CATBOXBOX_INCLUDE_SHIFTREGISTER_HPP_
#define CATBOXBOX_INCLUDE_SHIFTREGISTER_HPP_

#include <Arduino.h>
#include <stdint.h>

#define CHIP_INPUT_COUNT 8

namespace catbox {

// TODO: If more LED outputs are needed, extract ShiftRegister (abstract?) base class from Input74HC165
//  and extend ShiftRegister as Output74HC595 to drive output values.
//  Example?
//   ShiftRegister<VALUE_COUNT, CHIP_VALUE_COUNT>
//   InputShiftRegister<VC,CVC> extends ShiftRegister<VC,CVC>
//   Input74HC165<VC> extends InputShiftRegsiter<VC, 8>

template<int VALUE_COUNT>
class Input74HC165 {

  const uint8_t chipCount_ = (VALUE_COUNT / CHIP_INPUT_COUNT) + (((VALUE_COUNT % CHIP_INPUT_COUNT) == 0) ? 0 : 1);
  const uint8_t pinData_;
  const uint8_t pinClock_;
  const uint8_t pinLatch_;
  uint8_t values_[VALUE_COUNT];

 public:

  Input74HC165(uint8_t pin_data, uint8_t pin_clock, uint8_t pin_latch)
      : pinData_(pin_data),
        pinClock_(pin_clock),
        pinLatch_(pin_latch),
        values_{} {
    pinMode(pinData_, INPUT);
    pinMode(pinClock_, OUTPUT);
    pinMode(pinLatch_, OUTPUT);
  }

  void read() {
    // Load values into register
    digitalWrite(pinLatch_, LOW);
    delayMicroseconds(10);
    digitalWrite(pinLatch_, HIGH);

    // Read all values
    for (int i = 0; i < chipCount_; ++i) {
      values_[i] = shiftIn();
    }
  }

  bool getValue(uint8_t value_position) {
    // Out-of-range values are always false
    if (value_position < VALUE_COUNT) {
      return bitRead(values_[value_position / VALUE_COUNT], value_position % VALUE_COUNT) == 1;
    }
    return false;
  }

 private:

  uint8_t shiftIn() {
    uint8_t value = 0;
    uint8_t read;
    for (int i = 0; i < CHIP_INPUT_COUNT; ++i) {
      read = digitalRead(pinData_);
      digitalWrite(pinClock_, LOW);
      delay(1);
      digitalWrite(pinClock_, HIGH);
      value = (value << 1) | read;
    }
    return value;
  }

};

}

#endif //CATBOXBOX_INCLUDE_SHIFTREGISTER_HPP_
