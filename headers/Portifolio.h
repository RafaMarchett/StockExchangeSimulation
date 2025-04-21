#pragma once
#include "header.hpp"
#include "Stock.h"
#ifndef PORTIFOLIO
#define PORTIFOLIO
class Portifolio
{
    public:
    void printFullPortifolio() const;
    void buyStock(const std::unique_ptr<Stock>&, const size_t&);
    void sellStock(const std::unique_ptr<Stock>&, const size_t&);
    private:
    struct stockData
    {
        size_t totalStocks;
        float averagePrice;
        float totalParticipation = totalStocks*averagePrice;
    };
    float calculateAveragePrice(const std::unique_ptr<Stock>&,float,int);
    void calculateTotalParticipation(const std::unique_ptr<Stock>&);

    std::unordered_map<std::string,stockData> fullPortifolio;
}userPortifiolio;

#include "../src/Portifolio.cpp"
#endif // PORTIFOLIO