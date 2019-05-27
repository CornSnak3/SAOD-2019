#ifndef PASSENGER_H
#define PASSENGER_H

#include <iostream>
#include <string>

class Passenger {
private:
  std::string passportNumber, passportDateOfIssue, fullName, birthdayDate;

  bool validateNumber(std::string) const;

public:
  Passenger();
  Passenger(std::string);
  Passenger(std::string *);
  Passenger(Passenger *);
  ~Passenger();

  std::string getNumber() const;
  std::string getDateOfIssue() const;
  std::string getFullName() const;
  std::string getBirthdayDate() const;
  std::string getHashingValue() const;

  friend bool operator==(const Passenger, const Passenger);
  friend bool operator!=(const Passenger, const Passenger);
  friend std::ostream &operator<<(std::ostream &, const Passenger &);
};

#endif // PASSENGER_H
