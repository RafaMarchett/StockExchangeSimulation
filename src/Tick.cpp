#include "../headers/Tick.h"

Tick &Tick::getInstance() {
  static Tick tickStance;
  return tickStance;
}
size_t Tick::getTickIntervalMS() const { return tickIntervalMS; }
size_t Tick::getCurrentTimeMS() const {
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch())
      .count();
}
