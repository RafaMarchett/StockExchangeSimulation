#pragma once
#include "header.hpp"
#ifndef STOCK
#define STOCK

class Stock
{
    public:
    Stock(float, string, string);
    // void buy(std::unique_ptr<Portifolio>&);
    // void sell();
    string getTicker() const {return _ticker;}
    float getPrice() const {return _price;}
    
    private:
    float _price{0.0f};
    string _ticker, _companyName;
    
    
};

#include "../src/Stock.cpp"
#endif // STOCK