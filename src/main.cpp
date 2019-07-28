#include <Arduino.h>
#include "Clock.h"

#define LED_ON(Pin)   digitalWrite(Pin, HIGH)
#define LED_OFF(Pin)  digitalWrite(Pin, LOW)

// Uncomment to enable debug output via Serial console.
#define DEBUG_MODE

#define PIN_BZR     8
#define PIN_BTN     9
#define PIN_LED_GRN 12
#define PIN_LED_YLW 11
#define PIN_LED_RED 10

catbox::Clock clock;

boolean buttonPressed();
void playTest();

void setup() {
#ifdef DEBUG_MODE
  // Initialize serial console
  Serial.begin(9600);
  Serial.println("Serial console started.");
#endif

  // Setting output pins
  pinMode(PIN_BZR, OUTPUT);
  pinMode(PIN_LED_GRN, OUTPUT);
  pinMode(PIN_LED_YLW, OUTPUT);
  pinMode(PIN_LED_RED, OUTPUT);

  // Setting input pins
  pinMode(PIN_BTN, INPUT_PULLUP);

  // Setting default value to clock for debug purposes
  clock.set("1907276225200"); // 2019 July 27 Saturday(?) 10:52:00 PM
}

void loop() {
#ifdef DEBUG_MODE
  clock.print(Serial);
  delay(1000);
#endif
//  boolean pressed = buttonPressed();
//#ifdef DEBUG_MODE
//  Serial.print("Button pressed: ");
//  Serial.println(pressed ? "YES" : "NO");
//#endif
//  if (pressed) {
//    playTest();
//  }
}

boolean buttonPressed() {
  return !digitalRead(PIN_BTN);
}

void playTest() {
#ifdef DEBUG_MODE
  Serial.print("Starting LED/Buzzer test...");
#endif
  // Green LED, 1000hz
  LED_ON(PIN_LED_GRN);
  tone(PIN_BZR, 1000);
  delay(1000);
  LED_OFF(PIN_LED_GRN);
  // Yellow LED, 800hz
  LED_ON(PIN_LED_YLW);
  tone(PIN_BZR, 800);
  delay(1000);
  LED_OFF(PIN_LED_YLW);
  // Red LED, 600hz
  LED_ON(PIN_LED_RED);
  tone(PIN_BZR, 600);
  delay(1000);
  // Green, Yellow, Red LEDs, 1200hz
  LED_ON(PIN_LED_GRN);
  LED_ON(PIN_LED_YLW);
  tone(PIN_BZR, 1200);
  delay(1000);
  // Clean up
  LED_OFF(PIN_LED_GRN);
  LED_OFF(PIN_LED_YLW);
  LED_OFF(PIN_LED_RED);
  noTone(PIN_BZR);
#ifdef DEBUG_MODE
  Serial.print("Finished LED/Buzzer test.");
#endif
}