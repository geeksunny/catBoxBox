#ifndef CATBOXBOX_INCLUDE_CLOCK_H_
#define CATBOXBOX_INCLUDE_CLOCK_H_

#include <DS3231.h>

namespace catbox {

class Clock {
  DS3231 clock_;
 public:
  Clock();
  void print(Stream &stream);
  bool isTimeSet();
  bool set(const char *dateStr);
  bool setFrom(Stream &stream);
  bool setFrom(Stream &stream, unsigned long timeoutMillis);
  uint32_t now();
  uint32_t unixtimeSince(uint32_t unixtime);
  uint32_t secondsSince(uint32_t unixtime);
  uint32_t minutesSince(uint32_t unixtime);
  uint32_t hoursSince(uint32_t unixtime);
  uint32_t daysSince(uint32_t unixtime);
  uint32_t weeksSince(uint32_t unixtime);
  uint32_t monthsSince(uint32_t unixtime);
  uint32_t yearsSince(uint32_t unixtime);
};

}

#endif //CATBOXBOX_INCLUDE_CLOCK_H_
