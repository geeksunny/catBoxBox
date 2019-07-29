#include <Arduino.h>
#include "Clock.h"
#include "ShiftRegister.hpp"

#define LED_ON(Pin)           digitalWrite(Pin, HIGH)
#define LED_OFF(Pin)          digitalWrite(Pin, LOW)
#define IS_INPUT_ACTIVE(Pin)  (digitalRead(Pin) == LOW)

// Uncomment to enable debug output via Serial console.
#define DEBUG_MODE

// Input
#define PIN_BTN_RESET_TIMER     12
#define PIN_DIP_TIME_SET_MODE   7
// Output
#define PIN_BUZZER              8
// PWM Output
#define PIN_LED_GRN             11
#define PIN_LED_YLW             9
#define PIN_LED_RED             6
// 74HC165 I/O
#define PIN_74HC165_DATA        2 // IC-PIN-9, "SO" Serial-Output
#define PIN_74HC165_CLK         4 // IC-PIN-2, Clock
#define PIN_74HC165_LATCH       3 // IC-PIN-1, Shift / Load

catbox::Clock clock;
catbox::Input74HC165<8> dipSwitches(PIN_74HC165_DATA, PIN_74HC165_CLK, PIN_74HC165_LATCH);

void playTest();
void readShiftRegisterInput();

void setup() {
#ifdef DEBUG_MODE
  // Initialize serial console
  Serial.begin(9600);
  Serial.println("Serial console started.");
#endif

  // Setting output pins
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_LED_GRN, OUTPUT);
  pinMode(PIN_LED_YLW, OUTPUT);
  pinMode(PIN_LED_RED, OUTPUT);

  // Setting input pins
  pinMode(PIN_BTN_RESET_TIMER, INPUT_PULLUP);
  pinMode(PIN_DIP_TIME_SET_MODE, INPUT_PULLUP);

#ifdef DEBUG_MODE
  dipSwitches.read();
  Serial.println("DIP SWITCH VALUES:");
  for (int i = 0; i < 8; ++i) {
    Serial.print(" PIN ");
    Serial.print(i);
    Serial.print(" : ");
    Serial.println(dipSwitches.getValue(i) ? "ON" : "OFF");
  }
  Serial.print("9TH DIP SWITCH : ");
  Serial.println(IS_INPUT_ACTIVE(PIN_DIP_TIME_SET_MODE) ? "ON" : "OFF");
  Serial.print("BUTTON : ");
  Serial.println(IS_INPUT_ACTIVE(PIN_BTN_RESET_TIMER) ? "ON" : "OFF");
  while (true);
#endif

  // Setting default value to clock for debug purposes
  clock.set("1907276225200"); // 2019 July 27 Saturday(?) 10:52:00 PM

//  playTest();
//  while (true);
}

void loop() {
#ifdef DEBUG_MODE
  clock.print(Serial);
  delay(1000);
#endif
  boolean pressed = IS_INPUT_ACTIVE(PIN_BTN_RESET_TIMER);
#ifdef DEBUG_MODE
  Serial.print("Button pressed: ");
  Serial.println(pressed ? "YES" : "NO");
#endif
  if (pressed) {
    playTest();
  }
}

void playTest() {
#ifdef DEBUG_MODE
  Serial.print("Starting LED/Buzzer test...");
#endif
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
#endif
}

void readShiftRegisterInput() {

}