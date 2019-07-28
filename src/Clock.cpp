#include "Clock.h"
#include <Wire.h>

namespace catbox {

Clock::Clock() {
  // Start I2C interface
  Wire.begin();
}

void Clock::print(Stream &stream) {
  // Value containers
  bool Century, h12, PM;

  stream.print(clock_.getYear(), DEC);
  stream.print("-");
  stream.print(clock_.getMonth(Century), DEC);
  stream.print("-");
  stream.print(clock_.getDate(), DEC);
  stream.print(" ");
  stream.print(clock_.getHour(h12, PM), DEC); //24-hr
  stream.print(":");
  stream.print(clock_.getMinute(), DEC);
  stream.print(":");
  stream.println(clock_.getSecond(), DEC);
}

void Clock::set(const char *dateStr) {
  // dateStr format: YYMMDDwHHMMSS
  // TODO: data validation checks on dateStr contents?
  byte b1, b2;
  // Year
  b1 = (byte) dateStr[0] - 48;
  b2 = (byte) dateStr[1] - 48;
  clock_.setYear((b1 * 10) + b2);
  // Month
  b1 = (byte) dateStr[2] - 48;
  b2 = (byte) dateStr[3] - 48;
  clock_.setMonth((b1 * 10) + b2);
  // Date
  b1 = (byte) dateStr[4] - 48;
  b2 = (byte) dateStr[5] - 48;
  clock_.setDate((b1 * 10) + b2);
  // Day of Week
  clock_.setDoW((byte) dateStr[6] - 48);
  // Hour
  b1 = (byte) dateStr[7] - 48;
  b2 = (byte) dateStr[8] - 48;
  clock_.setHour((b1 * 10) + b2);
  // Minute
  b1 = (byte) dateStr[9] - 48;
  b2 = (byte) dateStr[10] - 48;
  clock_.setMinute((b1 * 10) + b2);
  // Second
  b1 = (byte) dateStr[11] - 48;
  b2 = (byte) dateStr[12] - 48;
  clock_.setSecond((b1 * 10) + b2);
}

bool Clock::setFrom(Stream &stream) {
  // todo: read dateStr from stream
  //  send it to set(dateStr)
  //  return true on success, false on error.
  return false;
}

}