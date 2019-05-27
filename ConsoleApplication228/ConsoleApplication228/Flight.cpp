#include <iomanip>
#include <iostream>
#include <string>

#include "Flight.h"

using namespace std;

void Flight::badCharHeuritics(string str, int size, int *badChar) {
  int i;
  for (i = 0; i < 64; i++)
    badChar[i] = -1;

  for (i = 0; i < size; i++)
    badChar[(int)str[i]] = i;
}

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
  this->freeSeats = stoi(s[7]);
}

Flight::~Flight() {}

bool Flight::searchBoyerMoore(string pattern) {
  string text = this->departureAirport;
  int m = pattern.size();
  int n = this->departureAirport.size();
  int *badChar = new int[64];
  badCharHeuritics(pattern, m, badChar);

  int shift = 0;
  while (shift <= (n - m)) {
    int j = m - 1;
    while (j >= 0 && pattern[j] == text[shift + j])
      j--;
    return (j < 0) ? true : false;
  }
  return false;
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
  o << setw(15) << left << f.number << setw(20) << left << f.company << setw(15)
    << left << f.departureAirport << setw(15) << left << f.arrivalAirport << setw(10)
    << left << f.departureDate << setw(10) << left << f.departureTime << setw(10) << left
    << f.freeSeats  << setw(10) << left << f.totalSeats << endl;
  return o;
}
