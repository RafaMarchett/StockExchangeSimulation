// #ifdef MARKET
#include "../headers/Market.h"
Market::Market()
{
  uniqueStock tempStocks[] = {
              std::make_unique<Stock>(30.42f,"RLS3","Ralsey's Hat"),
              std::make_unique<Stock>(100.31f,"MEG3","Major Explorer Group"),
              std::make_unique<Stock>(25.10f,"GLOB3","GlobalTech Solutions"),
              std::make_unique<Stock>(75.50f,"AFS3","Apex Financial Services"),
              std::make_unique<Stock>(75.3,"BNTG3","Backrooms Nonaligned Trade Group"),
              std::make_unique<Stock>(30.0f,"STRP3","Stroustrup's Code"),
              std::make_unique<Stock>(210.0f,"CHJK3","Chicken Jockey"),
              std::make_unique<Stock>(11.80f,"DATA3","SecureData Solutions"),
              std::make_unique<Stock>(50.23,"PRIT3","PrinTech Art 3D"),
              std::make_unique<Stock>(124.24,"MYS3","Mysticy Backrooms")
  };

  for(auto& stock : tempStocks)
  {
    if(!stock) std::cout << "ERROR\n;";
    addNewStock(stock);
  }
}

void Market::addNewStock(uniqueStock& newStock)
{
  if(newStock){
    allStocks.emplace(newStock->getTicker(),std::move(newStock));
  }
}
// #endif // MARKET