#include <iomanip>
#include <iostream>
#include <string>
#include <windows.h>

#include "Ticket.h"

Ticket::Ticket() { }


Ticket::Ticket(std::string* parameters) 
{
  passportNumber_ = parameters[0];
  flightNumber_   = parameters[1];
  ticketNumber_   = parameters[2];
  status = SOLD;
}


std::string Ticket::getTicketNumber()
{
  return ticketNumber_;
}


std::string Ticket::getFlightNumber()
{
  return flightNumber_;
}


bool Ticket::flipStatus()
{
  status = RETURNED;
  return true;
}



bool operator<(const Ticket& l, const Ticket& r)
{
  for (int i = 0; i < l.ticketNumber_.size(); i++) {
    if (l.ticketNumber_[i] < r.ticketNumber_[i]) {
      return true;
    }
  }
  
  return false;
}


bool operator==(const Ticket& r, const Ticket& l) 
{
  return 
    r.ticketNumber_   == l.ticketNumber_   &&
    r.passportNumber_ == l.passportNumber_ &&
    r.flightNumber_   == l.flightNumber_   &&
    r.status          == l.status;
}

// TODO

std::ostream &operator<<(std::ostream &o, const Ticket &t)
{
  std::string temp = (t.status == SOLD) ? "SOLD" : "RETURNED";
  std::cout << std::setw(15) << std::left << t.ticketNumber_ << std::setw(15) << std::left << t.flightNumber_ <<
    std::setw(15) << std::left << t.passportNumber_ << std::setw(10) << std::left << temp << std::endl; 
  return o;
}
