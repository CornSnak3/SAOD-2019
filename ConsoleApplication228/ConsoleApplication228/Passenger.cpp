#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "Passenger.h"

Passenger::Passenger() {}

Passenger::Passenger(std::initializer_list<std::string> &initList) {
  if ((initList.size() != fields.size()))
    throw new std::invalid_argument("INCORRECT PASSENGER INITIALIZATION");
  int count = 0;
  for (auto s : initList) {
    if (count == 0)
      if (!validateNumber(s))
        throw new std::invalid_argument("INVALID PASSPORT NUMBER");
    fields.at(count++).second = s;
  }
}

Passenger::Passenger(Passenger *p) {
  int count = 0;
  for (auto s : p->fields)
    fields.at(count++).second = s.second;
}

Passenger::~Passenger() { }

bool Passenger::validateNumber(std::string number) const {
  if (number[4] != '-' || number.size() != 11)
    return false;    
  for (unsigned int i = 0; i < number.size(); i++)
    if (!isdigit(number[i]) && number[i] != '-')
      return false;
  return true;
}

std::string Passenger::getField(std::string name) const {
  for (auto v : fields) {
    if (v.first == name)
      return v.second;
  }
  throw new std::invalid_argument("FIELD NOT FOUND");
}

std::vector<std::string> Passenger::getVector() const {
  std::vector<std::string> returnVector;
  for (auto p : fields)
    returnVector.push_back(p.second);
  return returnVector;
}

bool operator==(const Passenger &left, const Passenger &right) {
  if (left.fields.size() != right.fields.size())
    return false;
  bool result = false;
  for (int i = 0; i < left.fields.size(); i++) {
    if (left.fields.at(i).second != right.fields.at(i).second)
      return false;
  }
  return true;
}

bool operator!=(const Passenger &left, const Passenger &right) {
  return !(left == right);
}
