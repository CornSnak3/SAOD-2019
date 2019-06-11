#ifndef AIRFLIGHT_H
#define AIRFLIGHT_H

#include <string>
#include <vector>

class Flight {
private:
  std::vector<std::pair<std::string, std::string>> fields = {
    std::make_pair("flightNumber", ""),
    std::make_pair("company", ""),
    std::make_pair("departureAirport", ""),
    std::make_pair("arrivalAirport", ""),
    std::make_pair("departureDate", ""),
    std::make_pair("totalSeats", ""),
    std::make_pair("freeSeats", ""),
  };
  
  bool validateNumber(std::string) const ;

public:
  Flight();
  Flight(std::initializer_list<std::string> &);
  ~Flight();
  std::string getField(std::string);
  std::vector<std::string> getVector() const;
  bool searchBoyerMoore(std::string);

  bool operator<(Flight &);
  bool operator>(Flight &);
  bool operator==(Flight &);
};

#endif // AIRFLIGHT_H
