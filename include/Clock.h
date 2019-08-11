#ifndef CATBOXBOX_INCLUDE_CLOCK_H_
#define CATBOXBOX_INCLUDE_CLOCK_H_

#include <DS3231.h>

namespace catbox {

class Clock {
  DS3231 clock_;
 public:
  Clock();
  void print(Stream &stream);
  bool set(const char *dateStr);
  bool setFrom(Stream &stream);
  bool setFrom(Stream &stream, unsigned long timeoutMillis);
  uint32_t now();
};

}

#endif //CATBOXBOX_INCLUDE_CLOCK_H_
