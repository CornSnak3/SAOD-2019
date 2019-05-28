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

void Ticket::flipStatus() {
  this->status == (this->status == SOLD) ? RETURNED : SOLD;
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
  HANDLE  hConsole;
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  int c = (t.status == SOLD) ? 2 : 4;
  SetConsoleTextAttribute(hConsole, c);

  cout << setw(15) << t.ticketNumber << setw(15) << t.flightNumber << setw(15) << t.passportNumber << endl;
  SetConsoleTextAttribute(hConsole, 15);
 
  return o;
}
