#pragma once
#ifndef SYSTEMFUNCTIONS
#define SYSTEMFUNCTIONS
#include "header.hpp"

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else // LINUX/MAC
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#endif

class SysFuncs {

public:
  char getSingleKey();
  void pressEnterToContinue();
  int getTerminalLines();
  int getTerminalColumns();

private:
#ifdef _WIN32
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  int colluns{0}, rows{0};
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
  struct winsize w_size;
#endif // _WIN32
};

#endif // SYSTEMFUNCTIONS
