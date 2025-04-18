#pragma once
#include "header.hpp"
#include "Stock.h"
#ifndef PORTIFOLIO
#define PORTIFOLIO

class Portifolio
{
    public:
    void printFullPortifolio() const;
    void buyStock(std::unique_ptr<Stock>& buyedStock);
    private:
    std::unordered_map<string,unsigned int> fullPortifolio;
};
#include "../src/Portifolio.cpp"
#endif // PORTIFOLIO