#pragma once
#include "header.hpp"
#ifndef PORTIFOLIO
#define PORTIFOLIO

class Portifolio
{
    public:
    void buyStock(unique_ptr<Stock>& buyedStock);
    private:
    map<string,unsigned int> portifolioStocks;
};

#endif // PORTIFOLIO