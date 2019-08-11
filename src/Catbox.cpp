#include "Configuration.h"
#include "Catbox.h"

#define LED_ON(Pin)           digitalWrite(Pin, HIGH)
#define LED_OFF(Pin)          digitalWrite(Pin, LOW)
#define IS_INPUT_ACTIVE(Pin)  (digitalRead(Pin) == LOW)

namespace catbox {

////////////////////////////////////////////////////////////////
// Class : Catbox //////////////////////////////////////////////
////////////////////////////////////////////////////////////////

Catbox::Catbox()
    : buzzer_(Buzzer(PIN_BUZZER)),
      dipSwitches_(Input74HC165<8>(PIN_74HC165_DATA, PIN_74HC165_CLK, PIN_74HC165_LATCH)) {
  //
}

void Catbox::setup() {
  // Setting output pins
  pinMode(PIN_LED_GRN, OUTPUT);
  pinMode(PIN_LED_YLW, OUTPUT);
  pinMode(PIN_LED_RED, OUTPUT);

  // Setting input pins
  pinMode(PIN_BTN_RESET_TIMER, INPUT_PULLUP);
  pinMode(PIN_DIP_EXTRA_SWITCH, INPUT_PULLUP);

  // Read in values from DIP switches
  readDipSwitches();

  // Set clock from Serial if data available
  setClockFromSerial();

#ifdef DEBUG_MODE
  Serial.println("Serial console started.");
#endif //DEBUG_MODE
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
  // Digital Pin PIN_DIP_EXTRA_SWITCH: extraDipSwitch_
  extraDipSwitch_ = IS_INPUT_ACTIVE(PIN_DIP_EXTRA_SWITCH);
}

void Catbox::setClockFromSerial() {
  // TODO: optional timeout value for waiting on time data input
  Serial.begin(9600);
  while (!Serial) {
    // Waiting for serial ready
  }
  // Pause before reading from Serial
  delay(1000);
  if (Serial.available()) {
    // TODO: Signal start of time set from serial
    bool timeSet = clock_.setFrom(Serial);
    if (timeSet) {
      // TODO: End signal, success
    } else {
      // TODO: End signal, error
      // TODO: Invalid data received. Halt ??
    }
  }
  // TODO: Check for valid time data from clock_, half on invalid
}

}
