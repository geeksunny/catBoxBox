#include "Catbox.h"

namespace catbox {

////////////////////////////////////////////////////////////////
// Class : Catbox //////////////////////////////////////////////
////////////////////////////////////////////////////////////////

void Catbox::setup() {
  // Setting output pins
  pinMode(PIN_LED_GRN, OUTPUT);
  pinMode(PIN_LED_YLW, OUTPUT);
  pinMode(PIN_LED_RED, OUTPUT);

  // Setting input pins
  pinMode(PIN_BTN_RESET_TIMER, INPUT_PULLUP);
  pinMode(PIN_DIP_TIME_SET_MODE, INPUT_PULLUP);

  // Read in values from DIP switches
  readDipSwitches();

  if (timeSetMode_) {
    timeSetLoop();
  }

#ifdef DEBUG_MODE
  // Initialize serial console
  if (!timeSetMode_) {  // Serial.begin() has already been called if timeSetMode_ is TRUE
    Serial.begin(9600);
  }
  Serial.println("Serial console started.");
#endif //DEBUG_MODE

  // TODO: Check if clock has time set, set default value (compilation time via macro?) if none set
  //  - Breadboard a fresh RTC and see what default value is, if any.
}

void Catbox::loop() {
  boolean pressed = IS_INPUT_ACTIVE(PIN_BTN_RESET_TIMER);
#ifdef DEBUG_MODE
  Serial.print("Button pressed: ");
  Serial.println(pressed ? "YES" : "NO");
#endif //DEBUG_MODE
  if (pressed) {
    playTest();
  }
}

void Catbox::playTest() {
#ifdef DEBUG_MODE
  Serial.print("Starting LED/Buzzer test...");
#endif //DEBUG_MODE
  // Green LED, 1000hz
  LED_ON(PIN_LED_GRN);
  tone(PIN_BUZZER, 1000);
  delay(1000);
  LED_OFF(PIN_LED_GRN);
  // Yellow LED, 800hz
  LED_ON(PIN_LED_YLW);
  tone(PIN_BUZZER, 800);
  delay(1000);
  LED_OFF(PIN_LED_YLW);
  // Red LED, 600hz
  LED_ON(PIN_LED_RED);
  tone(PIN_BUZZER, 600);
  delay(1000);
  // Green, Yellow, Red LEDs, 1200hz
  LED_ON(PIN_LED_GRN);
  LED_ON(PIN_LED_YLW);
  tone(PIN_BUZZER, 1200);
  delay(1000);
  // Clean up
  LED_OFF(PIN_LED_GRN);
  LED_OFF(PIN_LED_YLW);
  LED_OFF(PIN_LED_RED);
  noTone(PIN_BUZZER);
#ifdef DEBUG_MODE
  Serial.print("Finished LED/Buzzer test.");
#endif //DEBUG_MODE
}

void Catbox::readDipSwitches() {
  dipSwitches_.read();
  // DIP Pins 1-6: timeout_, decimal addition.
  timeout_ = 0;
  for (int i = 0; i < 6; ++i) {
    if (dipSwitches_.getValue(i)) {
      timeout_ += (i + 1);
    }
  }
  // DIP Pin 7: Buzzer.enabled_
  if (dipSwitches_.getValue(6)) {
    buzzer_.enable();
    // DIP Pin 8: Buzzer.loudMode_
    buzzer_.setLoudMode(dipSwitches_.getValue(7));
  }
  // Digital Pin PIN_DIP_TIME_SET_MODE: timeSetMode_
  timeSetMode_ = IS_INPUT_ACTIVE(PIN_DIP_TIME_SET_MODE);
}

void Catbox::timeSetLoop() {
  // TODO: optional timeout value for waiting on time data input
  Serial.begin(9600);
  while (!Serial.available()) {
    // TODO: Handle blinking/pulsing LEDs within the loop
  }
  // TODO: start LED pattern for reading from serial
  if (!clock_.setFrom(Serial)) {
    // Failed to set clock from Serial input.
    // TODO: Should we halt on error here?
    //  Use LEDs to display error
    //  Use buzzer to sound error?
  }
  // TODO: Turn off any LEDs used in loop.
}

}
