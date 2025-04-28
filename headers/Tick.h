#pragma once

#include "header.hpp"
#ifndef TICK
#define TICK

using namespace std::chrono;
#define sleep std::this_thread::sleep_for

class Tick {
public:
  size_t getCurrentTimeMS() const;
  size_t getTickIntervalMS() const;
  static Tick &getInstance();

private:
  Tick() {}
  const size_t tickIntervalMS{100};
  int currentTick{0};
};

#endif // TICK
