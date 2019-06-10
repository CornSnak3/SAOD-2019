#ifndef TICKET_H
#define TICKET_H

#include <iostream>
#include <string>

enum TicketStatus { SOLD, RETURNED };

class Ticket {
private:
  std::string passportNumber, flightNumber, ticketNumber;
  TicketStatus status;
public:
  Ticket();
  Ticket(std::string *, TicketStatus);

  std::string getTicketNumber();

  bool flipStatus();
  std::string getFlightNumber();

  friend bool operator<(const Ticket &, const Ticket &);
  friend bool operator==(const Ticket &, const Ticket &);
  friend std::ostream &operator<<(std::ostream &, const Ticket &);
};

#endif TICKET_H