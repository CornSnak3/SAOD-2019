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

Flight::Flight(string *s, int *x) {
  this->number = s[0];
  this->company = s[1];
  this->departureAirport = s[2];
  this->arrivalAirport = s[3];
  this->departureDate = s[4];
  this->departureTime = s[5];
  this->totalSeats = x[0];
  this->freeSeats = x[1];
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
  o << setw(10) << right << f.number << setw(25) << f.company << setw(5) << right << f.departureAirport << "=>" <<
    setw(5) << f.arrivalAirport << setw(7) << f.departureTime << setw(4) << f.freeSeats << "/" << f.totalSeats << endl;
  return o;
}
