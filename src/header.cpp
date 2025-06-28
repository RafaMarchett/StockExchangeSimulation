#include "../headers/header.hpp"
#include "../headers/SystemFunctions.h"
void initializeLanguage() {
  char opt{'/'};
  SysFuncs SysFuncsManager;
  cout << clear;
  do {
    cout << "\nEnter 1 for English\n"
         << "Insira 2 para Portugues\n>>> " << std::flush;
    opt = SysFuncsManager.getSingleKey();
    if (opt == '1' || opt == '2') {
      language = opt;
      break;
    }
    cout << clear << "\nEnter a valid option\nInsira uma opção válida\n"
         << std::flush;
  } while (1);
}

void printInLanguage(const string &string1, const string &string2) {
  if (language == '1') {
    cout << string1;
  } else if (language == '2') {
    cout << string2;
  } else {
    initializeLanguage();
  }
  cout << std::flush;
}
