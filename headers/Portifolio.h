#pragma once
#include "header.hpp"
#include "Stock.h"
#ifndef PORTIFOLIO
#define PORTIFOLIO
class Portifolio
{
    public:
    void printFullPortifolio() const;
    void buyStock(const unique_ptr<Stock>&, const size_t&);
    void sellStock(const unique_ptr<Stock>&, const size_t&);
    private:
    struct stockData
    {
        size_t totalStocks;
        float averagePrice;
    };

    std::unordered_map<string,stockData> fullPortifolio;
}userPortifiolio;

#include "../src/Portifolio.cpp"
#endif // PORTIFOLIO