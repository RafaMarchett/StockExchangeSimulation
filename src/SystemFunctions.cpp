#include "../headers/SystemFunctions.h"

char SysFuncs::getSingleKey() {
  char keyPress{'/'};
#ifdef _WIN32
  keyPress = _getch();
#else
  set_terminal_raw_mode();
  read(STDIN_FILENO, &keyPress, 1); // read char
  restore_terminal_mode();
#endif
  return keyPress;
}

#ifndef _WIN32
void SysFuncs::if_not_original_termios_saved() {
  if (!original_termios_saved) {
    tcgetattr(STDIN_FILENO, &original_termios); // Get and save attributes
    original_termios_saved = true;
  }
}
void SysFuncs::set_terminal_raw_mode() {
  if_not_original_termios_saved();
  termios term = original_termios;
  term.c_lflag &= ~(ICANON | ECHO); // turn off echo and buffer(ICANON)
  tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void SysFuncs::set_terminal_no_echo_mode() {
  if_not_original_termios_saved();
  termios term = original_termios;
  term.c_lflag &= ~ECHO;
  term.c_lflag |= ICANON;
  tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void SysFuncs::restore_terminal_mode() {
  if (original_termios_saved) {
    tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
  }
}

termios original_termios;
bool original_termios_saved = false;
#endif // _WIN32

void SysFuncs::pressEnterToContinue() {
  printPressEnter();
  string dummy;
#ifdef _WIN32
  char c{'/'};
  do {
    c = _getch();
  } while (c != '\r' && c != '\n');
}
#else
  set_terminal_no_echo_mode();
  std::getline(cin, dummy);
  restore_terminal_mode();
#endif
}
