#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <algorithm>
#include <vector>
#include <functional>

#include "Passenger.h"

using namespace std;

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
  explicit HashTable(int initialCapacity = 64) {
    this->currentSize = 0;
    this->data = *(new vector<HashEntry>(64, HashEntry()));
  }

  void display() {
    cout << setw(15) << left << "PASSPORT #" << setw(20) << left << "DATE OF ISSUE" <<
      setw(40) << left << "FULL NAME" << setw(20) << left << "BIRTHDAY DATE" << endl;
    for (auto & hashEntry : data) {
      if (hashEntry.status == OCCUPIED)
        cout << hashEntry.value << endl;
    }
  }

  int loadFactor() {
    return (this->data.size() / this->data.capacity());
  }

  bool isOccupied(int currentPosition) const {
    return (data.at(currentPosition).status == OCCUPIED);
  }
  
  bool insert(const HashEntry &x) {
    int currentPosition = findPosition(x);
    if (data[currentPosition].status != REMOVED)
      ++this->currentSize;
	data[currentPosition].status = OCCUPIED;
	data[currentPosition].value = x.value;
	if (this->currentSize > this->data.capacity() / 2)
		rehash();
    return true;
  } 

  bool contains(string x) {
    Passenger passenger(x);
    HashEntry hashEntry(passenger);
    int currentPosition = hashCode(passenger);
    return (data[currentPosition].status == OCCUPIED &&
            data[currentPosition].value.getHashingValue() == hashEntry.value.getHashingValue());
  }

  void displaySearchByName(string x) {
    for (auto &p : this->data)
      if (p.value.getFullName == x)
        displaySearchByPassport(p.value.getNumber());
      else
        cout << "PASSENGER NOT FOUND" << endl;
  }

  void displaySearchByPassport(string x) {
    Passenger passenger(x);
    HashEntry hashEntry(passenger);
    int currentPosition = hashCode(passenger);
    if (data[currentPosition].status == OCCUPIED &&
        data[currentPosition].value.getHashingValue() == hashEntry.value.getHashingValue())
    {
      cout << setw(15) << left << "PASSPORT #" << setw(20) << left << "DATE OF ISSUE" <<
        setw(40) << left << "FULL NAME" << setw(20) << left << "BIRTHDAY DATE" << endl <<
        data[currentPosition].value;
    } else
      cout << "PASSENGER NOT FOUND" << endl;
  }

  bool remove(const HashEntry &x) {
    int currentPosition = findPosition(x) - 1;
    if (data[currentPosition].status != OCCUPIED)
      return false;
    if (data[currentPosition].value.getHashingValue() == x.value.getHashingValue()) {
      data[currentPosition].status = REMOVED;
      return true;
    }
    return false;
  }
  
  bool remove(std::string x) {
    Passenger passenger(x);
    HashEntry hashEntry(passenger);
    return remove(hashEntry);
  }
  
private:
  vector<HashEntry> data;
  unsigned int currentSize;

  size_t hashCode(Passenger value) const {
      uint64_t h = 17;
      int x = 31;
      for (const char &item : value.getHashingValue()) {
        h += item * x;
        x *= x;
      } 
      return h % this->data.capacity();
  }  
  


  int findPosition(const HashEntry &x) const {
    int offset = 1;
    int currentPosition = hashCode(x.value);
    while (data[currentPosition].status != EMPTY && data[currentPosition].value != x.value) {
      currentPosition += offset * offset;
      offset++;
      currentPosition = currentPosition % this->data.size();
    }    
    return currentPosition;          
  }

  void rehash() {
    vector<HashEntry> oldArray = this->data;
    this->data.resize(2 * oldArray.size());
    for (auto & hashEntry : data)
      hashEntry.status = EMPTY;

    currentSize = 0;
    for (auto & hashEntry : oldArray)
      if (hashEntry.status == OCCUPIED)
        insert(hashEntry);
  }

};

#endif // HASHTABLE_H
