#include "../headers/MarketEvents.h"

_marketEvents::allMembers marketEvents::getAllMembers() {
  _marketEvents::allMembers allMembers;
  allMembers.eventSector = eventSector;
  allMembers.eventTime = eventTime;

  return allMembers;
}
void marketEvents::setAllMembers(const _marketEvents::allMembers &inputStruct) {
  eventSector = inputStruct.eventSector;
  eventTime = inputStruct.eventTime;
}
void marketEvents::generateRandomEvent() {
  int randomSeedEvent = (rand() % 100) + 1;
  if (randomSeedEvent < 50)
  /*
  if (randomSeedEvent < 10) {

    // TODO: Aplicar evento...
    // NO MERCADO
    // Aplicar evento, recebe uma string com setor
    // Em todas as ações do setor, aplicar (positivo ou negativo)
    // Market::aplicarEvento("Clothing");
  }
  if (randomSeedEvent < 20) {
    // aplly in market("Sector")
  }
  if (randomSeedEvent < 30) {
  }
  if (randomSeedEvent < 40) {
  }
  if (randomSeedEvent < 50) {
  }
  if (randomSeedEvent < 60) {
  }
  if (randomSeedEvent < 70) {
  } else {
  }
  */
}
