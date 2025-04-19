#ifdef MARKET
#include "../headers/Market.h"

Market::Market()
{

}

void Market::addNewStock(unique_ptr<Stock>& newStock)
{
  if(newStock){
    // allStocks.insert(newStock->getTicker(),newStock);
  }
}
#endif // MARKET