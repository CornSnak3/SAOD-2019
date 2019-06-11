#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

namespace Utils {
  void printHeader(std::string);
  int executeMenu(const std::vector<std::string> &);
  void drawMenu(const std::vector<std::string> &, int);
  void printMenuItem(std::string, int, int, int);
  void getInput(std::string, std::string &, int);
}



#endif
