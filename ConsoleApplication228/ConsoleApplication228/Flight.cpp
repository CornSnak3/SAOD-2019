#include <iomanip>
#include <iostream>
#include <string>

#include "Flight.h"

using namespace std;

bool Flight::validateNumber(string) const  {
  return false;
}

Flight::Flight() {}

Flight::Flight(string s) {
  this->number = s;
}

Flight::Flight(string *s) {
  this->number = s[0];
  this->company = s[1];
  this->departureAirport = s[2];
  this->arrivalAirport = s[3];
  this->departureDate = s[4];
  this->departureTime = s[5];
  this->totalSeats = stoi(s[6]);
  this->freeSeats = totalSeats;
}

Flight::~Flight() {}

bool Flight::searchBoyerMoore(string substring) {
  string _string = this->departureAirport;
  int stringLength, substringLength;
  int res = -1;
  stringLength = _string.length();
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
    if (substring[substringLength - 1] != _string[position])
      position = position + boyerMooreTable[_string[position]];
    else
      for (i = substringLength - 2; i >= 0; i--) {
        if (substring[i] != _string[position - substringLength + i + 1]) {
          position += boyerMooreTable[_string[position - substringLength + i + 1]] - 1;
          break;
        } else if (i == 0)
            return true;
      }
  return false;
}

string Flight::getFlightNumber() const {
  return this->number;
}

int Flight::getFreeSeats() {
  return this->freeSeats;
}

void Flight::sellTicket() {
  this->freeSeats--;
}

void Flight::returnTicket() {
  this->freeSeats++;
}

bool operator==(const Flight &l, const Flight &r) {
  return (l.number == r.number);
}

bool operator>(const Flight &l, const Flight &r) {
  if (l.number > r.number)
    return true;
  else
    return false;
}

bool operator<(const Flight &l, const Flight &r) {
  if (l.number < r.number)
    return true;
  else
    return false;
}

ostream &operator<<(ostream &o, const Flight &f) {
  o << setw(15) << left << f.number << setw(20) << left << f.company << setw(25)
    << left << f.departureAirport << setw(25) << left << f.arrivalAirport << setw(10)
    << left << f.departureDate << setw(10) << left << f.departureTime << setw(10) << left
    << f.freeSeats  << setw(10) << left << f.totalSeats << endl;
  return o;
}
