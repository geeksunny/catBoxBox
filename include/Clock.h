#ifndef CATBOXBOX_INCLUDE_CLOCK_H_
#define CATBOXBOX_INCLUDE_CLOCK_H_

#include <DS3231.h>

namespace catbox {

class Clock {
  DS3231 clock_;
 public:
  Clock();
  void print(Stream &stream);
  void set(const char *dateStr);
  bool setFrom(Stream &stream);
  // todo: get()
};

}

#endif //CATBOXBOX_INCLUDE_CLOCK_H_
