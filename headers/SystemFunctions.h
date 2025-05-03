#pragma once
#ifndef SYSTEMFUNCTIONS
#define SYSTEMFUNCTIONS
#include "header.hpp"

#ifdef _WIN32
#include <conio.h>

#else // LINUX/MAC
#include <termios.h>
#include <unistd.h>

#endif

#ifdef _WIN32

#else

#endif // _WIN32
class SysFuncs {

public:
  char getSingleKey();
  void pressEnterToContinue();

private:
#ifdef _WIN32
  HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
  DWORD original_mode;
  GetConsoleMode(hConsole, &original_mode);
  SetConsoleMode(hConsole, original_mode); // To restore
#else
  void if_not_original_termios_saved();
  void set_terminal_raw_mode();

  void set_terminal_no_echo_mode();

  void restore_terminal_mode();

  termios original_termios;
  bool original_termios_saved = false;
#endif // _WIN32
};

#endif // SYSTEMFUNCTIONS
