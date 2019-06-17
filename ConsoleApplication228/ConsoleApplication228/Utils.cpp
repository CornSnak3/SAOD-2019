#include <conio.h>
#include <iostream>
#include <stack>
#include <string>
#include <Windows.h>

#include "Utils.h"

#define CONSOLE_COLOR_BLACK 0
#define CONSOLE_COLOR_BLUE  1
#define CONSOLE_COLOR_WHITE 7

void utils::printHeader(std::string header) {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, 16 * CONSOLE_COLOR_BLUE + CONSOLE_COLOR_WHITE);
  std::cout << header << std::endl;
  SetConsoleTextAttribute(hConsole, 16 * CONSOLE_COLOR_BLACK + CONSOLE_COLOR_WHITE);
}

