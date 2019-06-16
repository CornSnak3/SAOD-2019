#ifndef SAOD_HASHTABLE_H
#define SAOD_HASHTABLE_H

#include <algorithm>
#include <functional>
#include <string>
#include <vector>

#include "ConsoleTable.h"
#include "Passenger.h"

enum DataStatus { 
  OCCUPIED, EMPTY, REMOVED 
};

class HashEntry {

public: 
  HashEntry (void);
  HashEntry (Passenger&);
  ~HashEntry();

  Passenger  getValue  (void);
  DataStatus getStatus (void);
  
  void       setValue  (const Passenger&);
  void       setStatus (const DataStatus&);

private:
  Passenger  value_;
  DataStatus status_;

};



class HashTable { 

public:

  HashTable(int, ConsoleTable*, double, std::string&);
  
  double     getLoadFactor (void) const noexcept;
  int        getSize       (void) const noexcept;
  int        getCapacity   (void) const noexcept;

  bool       isOccupied    (int);
  bool       contains      (std::pair<std::string, std::string>&);
  int        insert        (HashEntry&);
  bool       remove        (std::pair<std::string, std::string>&);

  void       displaySearchByPassport (std::string&);
  void       displaySearchByName     (std::string&) const;

  HashEntry* find  (std::pair<std::string, std::string>&);
  
private:

  const double      MAX_LOAD_FACTOR;
  const std::string ID_FIELD_NAME;

  int size_;
  int capacity_;

  ConsoleTable*          linkedTable_;
  std::vector<HashEntry> data_;

  size_t     hashCode          (const std::string&) const;
  int        findEmptyPosition (const std::string&);
  int        findPosition      (const std::string&);
  bool       remove            (HashEntry&);
  void       rehash            (void);

  HashEntry* searchByPassport(std::string passportNumber);

};

#endif // SAOD_HASHTABLE_H
