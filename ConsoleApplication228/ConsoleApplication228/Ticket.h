#ifndef SAOD_TICKET_H
#define SAOD_TICKET_H

#include <iostream>
#include <string>

enum TicketStatus {
  SOLD, RETURNED
};


class Ticket {

public:

  Ticket(void);
  Ticket(std::string *);
  ~Ticket(void);

  bool flipStatus(void);

  std::string getFlightNumber(void);
  std::string getTicketNumber(void);

  friend bool          operator< (const Ticket&, const Ticket&);
  friend bool          operator==(const Ticket&, const Ticket&);
  friend std::ostream& operator<<(std::ostream&, const Ticket&);


private:

  std::string  passportNumber_, flightNumber_, ticketNumber_;
  TicketStatus status;

};

#endif // SAOD_TICKET_H