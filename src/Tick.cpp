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
bool Tick::getProgramIsRunning() const { return programIsRunning; }

size_t Tick::getCurrentTick() const { return currentTick; }
void Tick::incrementTick() { currentTick++; }

_Tick::allMembers Tick::getAllMembers() {
  _Tick::allMembers allMembers;
  allMembers.currentTick = currentTick;
  return allMembers;
}
void Tick::setAllMembers(_Tick::allMembers inputStruct) {
  currentTick = inputStruct.currentTick;
}
void Tick::endProgram() { programIsRunning = 0; }
