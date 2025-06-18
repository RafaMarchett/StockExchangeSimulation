#pragma once
#include "header.hpp"
#ifndef MARKETNEWS
#define MARKETNEWS

namespace _marketEvents {
struct allMembers {
  string currentEventSector;
  unsigned eventTime;
  Ternary bull_or_recessionMarket;
  signed int bull_or_recessionMarket_value;

  auto toTuple() {
    return std::tie(currentEventSector, eventTime,
                    bull_or_recessionMarket_value);
  }
};
} // namespace _marketEvents

class marketEvents {
public:
  void generateRandomEvent();
  static marketEvents &getMarketEvents();

  _marketEvents::allMembers getAllMembers();
  void setAllMembers(const _marketEvents::allMembers &);

private:
  marketEvents() = default;
  string currentEventSector = "";
  unsigned eventTime = 0;
  Ternary bull_or_recessionMarket;
};

#endif // MARKETNEWS
