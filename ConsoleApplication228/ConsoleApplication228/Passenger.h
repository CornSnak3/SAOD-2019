#ifndef PASSENGER_H
#define PASSENGER_H

#include <iostream>
#include <string>
#include <vector>

class Passenger {
private:
  std::vector<std::pair<std::string, std::string>> fields ={
    std::make_pair("passportNumber", ""),
    std::make_pair("passportDateOfIssue", ""),
    std::make_pair("fullName", ""),
    std::make_pair("birthdayDate", "")
  };

public:
  Passenger();
  Passenger(std::initializer_list<std::string> &);
  Passenger(Passenger *);
  ~Passenger();

  bool validateNumber(std::string) const;

  std::string getField(std::string) const;
  std::vector<std::string> getVector() const;

  friend bool operator==(const Passenger &, const Passenger &);
  friend bool operator!=(const Passenger &, const Passenger &);
};

#endif // PASSENGER_H
