#include <ctime>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <windows.h>

#include "Ticket.h"

Ticket::Ticket() { }


Ticket::Ticket(std::string* parameters) 
{
  passportNumber_ = parameters[0];
  flightNumber_   = parameters[1];
  ticketNumber_   = parameters[2];
  status_ = "Продан";
}


Ticket::Ticket(Passenger &passenger, Flight &flight)
{
  std::mt19937 gen { std::random_device()() };
  std::uniform_int_distribution<> uid(0, 9);
  std::string randomNumber;
  for (int i = 0; i < 9; i++) {
    randomNumber += std::to_string(uid(gen));
  }


  passportNumber_ = passenger.getField("passportNumber");
  flightNumber_   = flight.getField("flightNumber");
  ticketNumber_   = randomNumber;
  status_         = "Продан";
}


Ticket::~Ticket(void) { }



std::string Ticket::getTicketNumber()
{
  return ticketNumber_;
}


std::string Ticket::getFlightNumber()
{
  return flightNumber_;
}


std::vector<std::string> Ticket::getVector(void) const
{
  std::vector<std::string> returnVector;
  returnVector.push_back(ticketNumber_);
  returnVector.push_back(passportNumber_);
  returnVector.push_back(flightNumber_);
  returnVector.push_back(status_);

  return returnVector;
}


bool Ticket::flipStatus()
{
  status_ = "Возвращен";
  return true;
}



bool operator<(const Ticket& l, const Ticket& r)
{
  return l.ticketNumber_ < r.ticketNumber_;
}


bool operator==(const Ticket& r, const Ticket& l) 
{
  return
    r.ticketNumber_ == l.ticketNumber_;
}

