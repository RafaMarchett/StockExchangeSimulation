#pragma once
#include "header.hpp"
#ifndef MENUS
#define MENUS
class Menus
{
public:
  static void homeMenu()
  {
    std::cout << "ha\n";
  }
  // static void (); menu de negociacao
private:
  Menus();
};
#include "../src/Menus.cpp"
#endif // MENUS