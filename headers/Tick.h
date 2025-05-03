#pragma once

#include "header.hpp"
#ifndef TICK
#define TICK

using namespace std::chrono;
#define sleep std::this_thread::sleep_for

namespace _Tick {
struct allMembers {
  size_t currentTick{0};

  auto toTuple() { return std::tie(currentTick); }
};
} // namespace _Tick

class Tick {
public:
  size_t getCurrentTimeMS() const;
  size_t getTickIntervalMS() const;
  static Tick &getInstance();
  size_t getCurrentTick() const;
  void incrementTick();

  _Tick::allMembers getAllMembers();
  void setAllMembers(_Tick::allMembers);

private:
  Tick() {}
  const size_t tickIntervalMS{100};
  size_t currentTick{0};
};

#endif // TICK
