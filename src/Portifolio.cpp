#ifdef PORTIFOLIO
#include "../headers/Portifolio.h"

void Portifolio::buyStock(const unique_ptr<Stock>& buyedStock, const size_t& stockCount)
{
  if(buyedStock && stockCount > 0){
    if(fullPortifolio.find(buyedStock->getTicker()) != fullPortifolio.end())
    {
        fullPortifolio.find(buyedStock->getTicker())->second.totalStocks+=stockCount;
    }
    else
    {
        fullPortifolio.insert({buyedStock->getTicker(),{stockCount,buyedStock->getPrice()}});
    }
  }
}

void Portifolio::sellStock(const unique_ptr<Stock>& selledStock, const size_t& stockCounter) 
{
  auto& totalStocksInPortifolio = fullPortifolio.find(selledStock->getTicker())->second.totalStocks; 
    if(totalStocksInPortifolio >= stockCounter){
      totalStocksInPortifolio -= stockCounter;
    } 
    else{
      cout << "Você não possuí ações suficientes para vender\n";
    }
}
void Portifolio::printFullPortifolio() const
{
  for(auto& stock : fullPortifolio)
  {
    cout << bold << stock.first << noBold << " Preço médio: " << stock.second.averagePrice << " Quantidade: " << stock.second.totalStocks << '\n';
  }

}
#endif // PORTIFOLIO