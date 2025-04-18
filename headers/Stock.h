#pragma once
#include "header.hpp"
#include "Portifolio.h"
#ifndef STOCK
#define STOCK

class Stock
{
    public:
    // void buy(std::unique_ptr<Portifolio>&);
    // void sell();
    string getTicker() const {return ticker;}
    
    private:
    float price{0.0f};
    string ticker, companyName;
    
    
};

#endif // STOCK