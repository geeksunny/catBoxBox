#include <Arduino.h>

// Uncomment to enable debug output via Serial console.
#define DEBUG_MODE

#include "Catbox.h"

catbox::Catbox box;

void setup() {
  box.setup();
}

void loop() {
  box.loop();
}

void readShiftRegisterInput() {

}