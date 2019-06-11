#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <algorithm>
#include <functional>
#include <string>
#include <vector>

#include "ConsoleTable.h"
#include "Passenger.h"

enum DataStatus { OCCUPIED, EMPTY, REMOVED };

class HashEntry {
public:
  Passenger value;
  DataStatus status;
  HashEntry() : status(EMPTY) {}
  HashEntry(Passenger &p) : value(p), status(OCCUPIED) { }
  ~HashEntry() { }
};

class HashTable { 

public:
  HashTable(int, ConsoleTable *);
  std::string idFieldName = "passportNumber";

  const double maxLoadFactor = 0.75;

  double loadFactor(void) const;
  int getSize(void) const;
  bool isOccupied(int) const;

  bool insert(const HashEntry &);
  bool contains(std::pair<std::string, std::string> &);

  void displaySearchByPassport(std::string);
  void displaySearchByName(std::string);


  HashEntry *find(std::pair<std::string, std::string> &);
  bool remove(std::pair<std::string, std::string> &);
  
  std::vector<std::string> getCollisions(std::string);

private:
  std::vector<HashEntry> data;
  int capacity, size;
  ConsoleTable *linkedTable;

  size_t hashCode(const std::string &) const;
  HashEntry * searchByPassport(std::string passportNumber);
  int findEmptyPosition(const std::string &) const;
  int findPosition(const std::string &);
  bool remove(const HashEntry &);
  void rehash(void);
};

#endif // HASHTABLE_H
