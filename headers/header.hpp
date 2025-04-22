#pragma once
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <unordered_map>

// using std::ostream, std::std::cout, std::std::cin, std::std::string, std::std::unique_ptr, std::shared_ptr, std::std::make_unique;

std::ostream& bold(std::ostream& manip) {return manip << "\033[1m";}
std::ostream& noBold(std::ostream& manip) {return manip << "\033[0m";}

void configureFloat() {std::cout << std::fixed << std::setprecision(2);}