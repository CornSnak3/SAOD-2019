#include <iomanip>
#include <iostream>

#include "Passenger.h"

using namespace std;

Passenger::Passenger() {}

Passenger::Passenger(string x) {
  if (validateNumber(x))
    this->passportNumber = x;
  else
    throw new std::invalid_argument("INCORRECT PASSPORT NUMBER");
}

Passenger::Passenger(string *x) {
  if (!validateNumber(x[0]))
    throw new std::invalid_argument("INCORRECT PASSPORT NUMBER");
  this->passportNumber = x[0];
  this->passportDateOfIssue = x[1];
  this->fullName = x[2];
  this->birthdayDate = x[3];
}

Passenger::Passenger(Passenger *p) {
  this->passportNumber = p->passportNumber;
  this->passportDateOfIssue = p->passportDateOfIssue;
  this->fullName = p->fullName;
  this->birthdayDate = p->birthdayDate;
}

Passenger::~Passenger() { }

bool Passenger::validateNumber(string number) const {
  if (number[4] != '-' || number.size() != 11)
    return false;    
  for (unsigned int i = 0; i < number.size(); i++)
    if (!isdigit(number[i]) && number[i] != '-')
      return false;
  return true;
}

string Passenger::getNumber() const  {
  return this->passportNumber;
}

string Passenger::getDateOfIssue() const  {
  return this->passportDateOfIssue;
}

string Passenger::getFullName() const  {
  return this->fullName;
}

string Passenger::getBirthdayDate() const  {
  return this->birthdayDate;
}

string Passenger::getHashingValue() const  {
  return passportNumber;
}

ostream &operator<<(ostream &o, const Passenger &p) {
  string fullName = (p.fullName.size() > 38) ? p.fullName.substr(0, 38) : p.fullName;
  string issueDate = (p.passportDateOfIssue.size() > 18) ? p.getDateOfIssue().substr(0, 18) : p.getDateOfIssue();

  o << setw(15) << left << p.getNumber() << setw(20) << left << issueDate <<
    setw(40) << left << fullName << setw(20) << left << p.getBirthdayDate() << endl;
  return o;
}

bool operator==(const Passenger left, const Passenger right) {
  return (left.passportNumber == right.passportNumber) &&
    (left.passportDateOfIssue == right.passportDateOfIssue) &&
    (left.birthdayDate == right.birthdayDate) &&
    (left.fullName == right.fullName);
}

bool operator!=(const Passenger left, const Passenger right) {
  return !(left == right);
}
