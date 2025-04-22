#pragma once
#include "header.hpp"
#include "Stock.h"
#ifndef PORTIFOLIO
#define PORTIFOLIO
class Portifolio
{
    public:
    void printFullPortifolio() const;
    void buyStock(const uniqueStock&, const size_t&);
    void sellStock(const uniqueStock&, const size_t&);
    private:
    struct stockData
    {
        size_t totalStocks;
        float averagePrice;
        float totalParticipation = totalStocks*averagePrice;
    };
    float calculateAveragePrice(const uniqueStock&,float,int);
    void calculateTotalParticipation(const uniqueStock&);

    std::unordered_map<std::string,stockData> fullPortifolio;
}userPortifiolio;

#include "../src/Portifolio.cpp"
#endif // PORTIFOLIO