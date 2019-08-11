#include "Clock.h"
#include <Wire.h>

#define TIME_STR_LEN 13

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

bool Clock::set(const char *dateStr) {
  // dateStr format: YYMMDDwHHMMSS
  for (int i = 0; i < TIME_STR_LEN; ++i) {
    if (!isdigit(dateStr[i])) {
      // Invalid input; non-digit character found
      return false;
    }
  }
  // TODO: Set 12/24hr mode here.
  //  Should 12 or 24 be used? does it matter?
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
  // Clock set successful
  return true;
}

bool Clock::setFrom(Stream &stream) {
  // Ignore everything until digit is received.
  //  Error if invalid character is found after first digit, before expected length
  if (stream.available()) {
    // TODO: Clean up this logic to be clearer / easier to follow
    char buf[TIME_STR_LEN];
    int i = 0;
    bool started = false;
    while (stream.available()) {
      if (started) {
        buf[i] = stream.read();
        if (!isdigit(buf[i++])) {
          // invalid input; non-digit character found
          return false;
        }
        // Do we have all the data we're looking for?
        if (i == TIME_STR_LEN) {
          // Discard remaining input data
          while (stream.available()) {
            stream.read();
          }
          // Set clock with buffer contents
          return set(buf);
        }
      } else {
        // Ignore non-digit characters
        if (isdigit(stream.peek())) {
          started = true;
        } else {
          stream.read();
        }
      }
    }
  }
  return false;
}

bool Clock::setFrom(Stream &stream, unsigned long timeoutMillis) {
  // TODO: Keep time with millis(), do not rely on stream.available()
  return false;
}

uint32_t Clock::now() {
  return RTClib::now().unixtime();
}

}