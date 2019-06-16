#ifndef SAOD_FLIGHT_H
#define SAOD_FLIGHT_H

#include <string>
#include <vector>

class Flight {

public:

  Flight  (void);
  Flight  (std::initializer_list<std::string> &);

  ~Flight (void);

  std::vector<std::string> getVector (void) const;
  std::string              getField  (std::string);

  bool searchBoyerMoore (std::string);

  bool operator<  (Flight &);
  bool operator>  (Flight &);
  bool operator== (Flight &);

private:

  std::vector<std::pair<std::string, std::string>> fields = {
    std::make_pair("flightNumber",     ""),
    std::make_pair("company",          ""),
    std::make_pair("departureAirport", ""),
    std::make_pair("arrivalAirport",   ""),
    std::make_pair("departureDate",    ""),
    std::make_pair("totalSeats",       ""),
    std::make_pair("freeSeats",        ""),
  };
  
  bool validateNumber(std::string) const;

};

#endif // SAOD_FLIGHT_H
