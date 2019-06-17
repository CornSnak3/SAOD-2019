#ifndef SAOD_TICKET_H
#define SAOD_TICKET_H

#include <iostream>
#include <string>

#include "Flight.h"
#include "Passenger.h"


class Ticket {

public:

  Ticket  (void);
  Ticket  (std::string *);
  Ticket  (Passenger&, Flight&);

  ~Ticket (void);

  bool flipStatus(void);

  std::string getFlightNumber(void);
  std::string getTicketNumber(void);

  std::vector<std::string> getVector(void) const;

  friend bool operator< (const Ticket&, const Ticket&);
  friend bool operator==(const Ticket&, const Ticket&);
  

private:

  std::string  passportNumber_, flightNumber_,
               ticketNumber_, status_;

};

#endif // SAOD_TICKET_H