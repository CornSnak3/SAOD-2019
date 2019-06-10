#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "Flight.h"


bool Flight::validateNumber(std::string) const  {
  return false;
}

Flight::Flight() {}

Flight::Flight(std::initializer_list<std::string> &initList) {
  if ((initList.size() != fields.size()))
    throw new std::invalid_argument("INCORRECT FLIGHT INITIALIZATION");
  int count = 0;
  for (auto s : initList) {
    if (count == 0)
      if (!validateNumber(s))
        throw new std::invalid_argument("INVALID FLIGHT NUMBER");
    fields.at(count++).second = s;
  }
}

std::string Flight::getField(std::string fieldName) {
  for (auto field : fields) {
    if (field.first == fieldName)
      return field.second;
  }
  throw new std::invalid_argument("FIELD NOT FOUND");
}

Flight::~Flight() {}

bool Flight::searchBoyerMoore(std::string substring) {
  std::string string = getField("departureAirport");
  int stringLength, substringLength;
  int res = -1;
  stringLength = string.length();
  substringLength = substring.length();
  if (stringLength < substringLength)
    return false;
  int i, position;
  int boyerMooreTable[128];
  for (i = 0; i < 128; i++)
    boyerMooreTable[i] = substringLength;
  for (i = substringLength - 1; i >= 0; i--)
    if (boyerMooreTable[substring[i]] == substringLength)
      boyerMooreTable[substring[i]] = substringLength - i - 1;
  position = substringLength - 1;
  while (position < stringLength)
    if (substring[substringLength - 1] != string[position])
      position = position + boyerMooreTable[string[position]];
    else
      for (i = substringLength - 2; i >= 0; i--) {
        if (substring[i] != string[position - substringLength + i + 1]) {
          position += boyerMooreTable[string[position - substringLength + i + 1]] - 1;
          break;
        } else if (i == 0)
            return true;
      }
  return false;
}

bool Flight::operator<(Flight &rvalue) {
  return (this->getField("flightNumber") < rvalue.getField("flightNumber"));
}

bool Flight::operator>(Flight &rvalue) {
  return (this->getField("flightNumber") > rvalue.getField("flightNumber"));
}

bool Flight::operator==(Flight &rvalue) {
  return (this->getField("flightNumber") == rvalue.getField("flightNumber"));
}