#include "Passenger.h"

using namespace std;

Passenger::Passenger() {}

Passenger::Passenger(string x) {
  this->passportNumber = x;
}

Passenger::Passenger(string *x) {
  //if (!validateNumber(x[0]))
    //throw new std::invalid_argument("Некорректный номер паспорта");
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
  if (passportNumber.size() != 11)
    return false;
  if (passportNumber[4] != '-')
    return false;
    
  for (unsigned int i = 0; i < passportNumber.size(); i++) {
    if (i == 4)
      continue;
    if (!isdigit(passportNumber[i]))
      return false;
  }
  
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
  o << p.getNumber() << "\t" << p.getDateOfIssue() << "\t" <<
    p.getFullName() << "\t" << p.getBirthdayDate() << endl;
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
