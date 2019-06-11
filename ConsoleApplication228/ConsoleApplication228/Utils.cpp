#include <conio.h>
#include <iostream>
#include <stack>
#include <string>
#include <Windows.h>

#include "Utils.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ESC 27
#define KEY_ENTER '\r'

#define CONSOLE_COLOR_BLACK 0
#define CONSOLE_COLOR_BLUE  1
#define CONSOLE_COLOR_WHITE 7

const std::string helpString1 = "ббепу/бмхг(ярпекйх)";
const std::string helpString2 = "бшунд(ESC) | ббнд(ENTER)";

void Utils::printHeader(std::string header) {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, 16 * CONSOLE_COLOR_BLUE + CONSOLE_COLOR_WHITE);
  std::cout << header << std::endl;
  SetConsoleTextAttribute(hConsole, 16 * CONSOLE_COLOR_BLACK + CONSOLE_COLOR_WHITE);
}

int Utils::executeMenu(const std::vector<std::string> &menu) {
  char keyPressed;
  int currentPosition = 0;
  while (true) {
    drawMenu(menu, currentPosition + 1);
    keyPressed = _getch();
    switch (keyPressed) {
    case KEY_ESC:
      return -1;
    case KEY_DOWN:
      if (currentPosition < menu.size())
        currentPosition++;
      break;
    case KEY_UP:
      if (currentPosition > 0)
        currentPosition--;
      break;
    case KEY_ENTER:
      return currentPosition;
    default:
      break;
    }
  }
  return 0;
}

void Utils::drawMenu(const std::vector<std::string> &menu,
                     int highlintedMenuItem) {
  system("cls");
  size_t maxLength = helpString2.size();
  for (auto s : menu) {
    if (s.size() > maxLength)
      maxLength = s.size();
  }
  const int whiteColor = 15, blackColor = 0, blueColor = 1;
  printMenuItem(menu[0], maxLength, blueColor, whiteColor);
  int position = 1;
  while (position < menu.size()) {
    if (position == highlintedMenuItem)
      printMenuItem(menu[position], maxLength, whiteColor, blackColor);
    else
      printMenuItem(menu[position], maxLength, blackColor, whiteColor);
    position++;
  }
  std::cout << std::endl;
  printMenuItem(helpString1, maxLength, 8, 15);
  printMenuItem(helpString2, maxLength, 8, 15);

}

void Utils::printMenuItem(std::string menuItem, int length,
                          int backgroundColor, int foregroundColor) {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  if (menuItem.size() % 2 == 1)
    menuItem = " " + menuItem;
  std::string paddingString((length - menuItem.size()) / 2 + 10 , ' ');
  SetConsoleTextAttribute(hConsole, 16 * backgroundColor + foregroundColor);
  std::string temp = paddingString + menuItem + paddingString;
  std::cout << temp << std::endl;
  SetConsoleTextAttribute(hConsole, 16 * 0 + 7);
}

void Utils::getInput(std::string fieldName, std::string &objectToWrite, int maxLength) {
  std::string paddingString(maxLength - fieldName.size(), ' ');
  std::cout << fieldName << paddingString << ">> ";
  getline(std::cin, objectToWrite);
  std::cin.clear();
}
