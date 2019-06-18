#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "Flight.h"

//Public Flight

Flight::Flight(void) { }


Flight::Flight(std::initializer_list<std::string>& initializationList)
{
  if ((initializationList.size() != fields.size())) {
    throw new std::invalid_argument("Incorrect Flight initialization");
  }

  int count = 0;
  for (auto s : initializationList) {
    if (count == 0) {
      if (!validateNumber(s)) {
        throw new std::invalid_argument("Invalid flight number");
      }
    }

    fields.at(count).second = s;
    count++;
  }
}


Flight::~Flight() {}



std::vector<std::string> Flight::getVector() const
{
  std::vector<std::string> returnVector;
  for (auto field : fields) {
    returnVector.push_back(field.second);
  }

  return returnVector;
}


std::string Flight::getField(std::string fieldName)
{
  for (auto& field : fields) {
    if (field.first == fieldName) {
      return field.second;
    }
  }

  throw new std::invalid_argument("Field not found");
}


bool Flight::searchBoyerMoore(std::string substring)
{
  std::string string = getField("departureAirport");
  
  int res             = -1;
  int stringLength    = string.length();
  int substringLength = substring.length();

  if (stringLength < substringLength) {
    return false;
  }

  int i;
  int position = substringLength - 1;
  int BMT[256];

  for (i = 0; i < 256; i++) {
    BMT[i] = substringLength;
  }

  for (i = substringLength - 1; i >= 0; i--) {
    if (BMT[static_cast<int>(substring[i] + 128)] == substringLength) {
      BMT[static_cast<int>(substring[i] + 128)] = substringLength - i - 1;
    }
  }

  while (position < stringLength) {
    if (substring[substringLength - 1] != string[position]) {
      position = position + BMT[static_cast<int> (string[position] + 128)];
    }
    else {
      for (i = substringLength - 2; i >= 0; i--) {
        char characterToCheck = string[position - substringLength + i + 1];
        if (substring[i] != characterToCheck) {
          position += BMT[static_cast<int>(characterToCheck + 128)] - 1;
          break;
        }
        else {
          if (i == 0)
          {
            return true;
          }
        }
      }
    }
  }

  return false;
}





bool Flight::operator<(Flight &rvalue)
{
  return (this->getField("flightNumber") < rvalue.getField("flightNumber"));
}


bool Flight::operator>(Flight &rvalue)
{
  return (this->getField("flightNumber") > rvalue.getField("flightNumber"));
}


bool Flight::operator==(Flight &rvalue)
{
  return (this->getField("flightNumber") == rvalue.getField("flightNumber"));
}



// Private Flight

bool Flight::validateNumber(std::string passpornNo) const
{
  if (passpornNo[3] != '-' || passpornNo.size() != 7) {
    return false;
  }

  passpornNo.erase(passpornNo.begin() + 3);

  for (int i = 0; i < passpornNo.size(); i++) {
    if (!isdigit(passpornNo[i])) {
      return false;
    }
  }

  return true;
}