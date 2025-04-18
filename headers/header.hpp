#pragma once
#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <unordered_map>
#include <fstream>
#include <memory>

using std::ostream, std::cout, std::cin, std::string;

ostream& bold(ostream& manip) {return manip << "\033[1m";}
ostream& noBold(ostream& manip) {return manip << "\033[0m";}