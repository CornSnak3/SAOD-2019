#ifndef AIRFLIGHT_H
#define AIRFLIGHT_H

#include <string>

class Flight {
private:
  std::string number, company, departureAirport, arrivalAirport;
  std::string departureDate, departureTime;
  unsigned int totalSeats, freeSeats;
  
  bool validateNumber(std::string) const ;

public:
  Flight();
  Flight(std::string);
  Flight(std::string *);
  ~Flight();

  bool searchBoyerMoore(std::string);

  int getFreeSeats();
  void sellTicket();

  friend bool operator==(const Flight &, const Flight &);
  friend bool operator>(const Flight &, const Flight &);
  friend bool operator<(const Flight &, const Flight &);
  friend std::ostream &operator<<(std::ostream &, const Flight &);
};

#endif // AIRFLIGHT_H
