#include <Arduino.h>

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