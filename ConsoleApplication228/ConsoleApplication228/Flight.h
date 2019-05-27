#ifndef AIRFLIGHT_H
#define AIRFLIGHT_H

#include <string>

class Flight {
private:
  std::string number, company, departureAirport, arrivalAirport;
  std::string departureDate, departureTime;
  unsigned int totalSeats, freeSeats;
  
  bool validateNumber(std::string) const ;
  void badCharHeuritics(std::string, int, int *);

public:
  Flight();
  Flight(std::string *, int *);
  ~Flight();

  bool searchBoyerMoore(std::string);

  friend bool operator>(const Flight &, const Flight &);
  friend bool operator<(const Flight &, const Flight &);
  friend std::ostream &operator<<(std::ostream &, const Flight &);
};

#endif // AIRFLIGHT_H
