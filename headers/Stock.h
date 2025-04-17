#pragma once
#include "header.hpp"
#ifndef STOCK
#define STOCK

class Stock
{
    public:
    void buy(unique_ptr<Portifolio>&);
    void sell();
    
    private:
    float price{0.0f};
    string ticker, companyName;
    
    
};

#endif // STOCK