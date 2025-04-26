#ifdef MENUS
#include "../headers/Menus.h"
void Menus::changeStockOnScreen(bool newState) {
  Market tempMarket = Market::getMarket();
  tempMarket.setStockOnScreen(newState);
}
#endif
