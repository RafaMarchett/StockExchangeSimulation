#pragma once
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

using std::ostream, std::cout, std::cin, std::string, std::shared_ptr,
    std::shared_ptr, std::make_shared, std::vector, std::setw;
const string upArrow{"\033[32m▲\033[37m"}, downArrow{"\033[31m▼\033[37m"};

ostream &bold(ostream &manip) { return manip << "\033[1m"; }
ostream &noBold(ostream &manip) { return manip << "\033[0m"; }

void configureFloat() { cout << std::fixed << std::setprecision(2); }
