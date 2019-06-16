#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "Passenger.h"

Passenger::Passenger(void) { }


Passenger::Passenger(std::initializer_list<std::string>& initList) 
{
  if ((initList.size() != fields.size())) {
    throw new std::invalid_argument("INCORRECT PASSENGER INITIALIZATION");
  }
  int count = 0;
  for (auto s : initList) {
    if (count == 0) {
      if (!validatePassportNo(s)) {
        throw new std::invalid_argument("INVALID PASSPORT NUMBER");
      }
    }
    fields.at(count).second = s;
    count++;
  }
}



Passenger::Passenger(Passenger* p) 
{
  int count = 0;
  for (auto s : p->fields) {
    fields.at(count++).second = s.second;
  }
}



Passenger::~Passenger(void) { }



bool Passenger::validatePassportNo(std::string passportNo) const 
{
  int passportNoSize = passportNo.size();

  if (passportNo[4] != '-' || passportNoSize != 11) {
    return false;
  }

  passportNo.erase(passportNo.begin() + 4);

  for (int i = 0; i < passportNoSize; i++) {
    if (!isdigit(passportNo[i])) {
      return false;
    }
  }

  return true;
}



std::string Passenger::getField(std::string name) const 
{
  for (auto v : fields) {
    if (v.first == name) {
      return v.second;
    }
  }

  throw new std::invalid_argument("FIELD NOT FOUND");
}



std::vector<std::string> Passenger::getVector(void) const 
{
  std::vector<std::string> returnVector;
  for (auto p : fields) {
    returnVector.push_back(p.second);
  }
  return returnVector;
}



bool operator==(const Passenger& l, const Passenger& r)
{
  if (l.fields.size() != r.fields.size()) {
    return false;
  }

  for (int i = 0; i < l.fields.size(); i++) {
    if (l.fields.at(i).second != r.fields.at(i).second) {
      return false;
    }
  }

  return true;
}



bool operator!=(const Passenger& l, const Passenger& r)
{
  return !(l == r);
}
