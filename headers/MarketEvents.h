#pragma once
#include "header.hpp"
#ifndef MARKETNEWS
#define MARKETNEWS

namespace _marketEvents {
struct allMembers {
  string eventSector;
  unsigned eventTime;

  auto toTuple() { return std::tie(eventSector, eventTime); }
};
} // namespace _marketEvents

class marketEvents {
public:
  void generateRandomEvent();

  _marketEvents::allMembers getAllMembers();
  void setAllMembers(const _marketEvents::allMembers &);

private:
  string eventSector = "";
  unsigned eventTime;
};

#endif // MARKETNEWS
