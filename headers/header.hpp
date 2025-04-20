#pragma once
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <unordered_map>

using std::ostream, std::cout, std::cin, std::string, std::unique_ptr, std::shared_ptr, std::make_unique;

ostream& bold(ostream& manip) {return manip << "\033[1m";}
ostream& noBold(ostream& manip) {return manip << "\033[0m";}

void configureFloat() {cout << std::fixed << std::setprecision(2);}