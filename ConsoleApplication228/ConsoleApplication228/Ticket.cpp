#include <iomanip>
#include <iostream>
#include <string>
#include <windows.h>

#include "Ticket.h"

using namespace std;

Ticket::Ticket() {
  this->ticketNumber = "999999999";
}


Ticket::Ticket(string *s, TicketStatus ts) {
  this->passportNumber = s[0];
  this->flightNumber = s[1];
  this->ticketNumber = s[2];
  this->status = ts;
}

string Ticket::getTicketNumber() {
  return this->ticketNumber;
}

string Ticket::getFlightNumber() {
  return this->flightNumber;
}

bool Ticket::flipStatus() {
  this->status = RETURNED;
  return true;
}

bool operator<(const Ticket &l, const Ticket &r) {
  for (int i = 0; i < l.ticketNumber.size(); i++)
    if (l.ticketNumber[i] < r.ticketNumber[i])
      return true;
  return false;
}

bool operator==(const Ticket &r, const Ticket &l) {
  return (r.ticketNumber == l.ticketNumber) &&
    (r.passportNumber == l.passportNumber) &&
    (r.flightNumber == l.flightNumber) &&
    (r.status == l.status);
}

ostream &operator<<(ostream &o, const Ticket &t) {
  string temp = (t.status == SOLD) ? "SOLD" : "RETURNED";
  cout << setw(15) << left << t.ticketNumber << setw(15) << left << t.flightNumber <<
    setw(15) << left << t.passportNumber << setw(10) << left << temp << endl; 
  return o;
}
