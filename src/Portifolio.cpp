#ifdef PORTIFOLIO
#include "../headers/Portifolio.h"

void Portifolio::buyStock(std::unique_ptr<Stock>& buyedStock)
{
  if(fullPortifolio.find(buyedStock->getTicker()) != fullPortifolio.end())
  {
      fullPortifolio.find(buyedStock->getTicker())->second++;
  }
  else
  {
      fullPortifolio.insert({buyedStock->getTicker(),1});
  }
}

void Portifolio::printFullPortifolio() const
{
  for(auto& c : fullPortifolio)
  {
    cout << c.first << ' ' << c.second << '\n';
  }

}
#endif // PORTIFOLIO