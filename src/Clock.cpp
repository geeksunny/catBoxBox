#include "Clock.h"
#include <Wire.h>

#define TIME_STR_LEN        13

#define MINUTE_IN_SECONDS   60
#define HOUR_IN_SECONDS     3600
#define DAY_IN_SECONDS      86400
#define WEEK_IN_SECONDS     604800
#define MONTH_IN_SECONDS    2629743
#define YEAR_IN_SECONDS     31556926

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

bool Clock::isTimeSet() {
  // Default time values are zero. Finding a zero value in most fields should indicate an unset clock.
  // Note: This will evaluate to TRUE after the first 24 hours of operation.
  bool Century;
  return ((int) clock_.getYear() != 0) && ((int) clock_.getMonth(Century) != 0) && ((int) clock_.getDate() != 0);
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

uint32_t Clock::unixtimeSince(const uint32_t unixtime) {
  return now() - unixtime;
}

uint32_t Clock::secondsSince(uint32_t unixtime) {
  return unixtimeSince(unixtime);
}

uint32_t Clock::minutesSince(uint32_t unixtime) {
  uint32_t since = unixtimeSince(unixtime);
  uint32_t minutes = since / MINUTE_IN_SECONDS;
  return minutes;
}

uint32_t Clock::hoursSince(uint32_t unixtime) {
  uint32_t since = unixtimeSince(unixtime);
  uint32_t hours = since / HOUR_IN_SECONDS;
  return hours;
}

uint32_t Clock::daysSince(uint32_t unixtime) {
  uint32_t since = unixtimeSince(unixtime);
  uint32_t days = since / DAY_IN_SECONDS;
  return days;
}

uint32_t Clock::weeksSince(uint32_t unixtime) {
  uint32_t since = unixtimeSince(unixtime);
  uint32_t weeks = since / WEEK_IN_SECONDS;
  return weeks;
}

uint32_t Clock::monthsSince(uint32_t unixtime) {
  uint32_t since = unixtimeSince(unixtime);
  uint32_t months = since / MONTH_IN_SECONDS;
  return months;
}

uint32_t Clock::yearsSince(uint32_t unixtime) {
  uint32_t since = unixtimeSince(unixtime);
  uint32_t years = since / YEAR_IN_SECONDS;
  return years;
}

}