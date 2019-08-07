#include "Configuration.h"
#include "Buzzer.h"

namespace catbox {

////////////////////////////////////////////////////////////////
// Class : Buzzer //////////////////////////////////////////////
////////////////////////////////////////////////////////////////

Buzzer::Buzzer(const uint8_t pin) : enabled_(false), loudMode_(false), pin_(pin), pattern_(BuzzerPattern::Tone) {
  //
}

void Buzzer::enable() {
  if (!enabled_) {
    enabled_ = true;
    pinMode(pin_, OUTPUT);
  }
}

void Buzzer::disable() {
  if (enabled_) {
    enabled_ = false;
    // TODO: Reset pinMode() ?
  }
}

void Buzzer::setLoudMode(const bool enabled) {
  loudMode_ = enabled;
}

}