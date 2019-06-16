#include <algorithm>
#include <iostream>
#include <string> 
#include <Windows.h>

#include "HashTable.h"
#include "Utils.h"

// Public HashEntry

HashEntry::HashEntry(void) : 
  status_(EMPTY), value_(nullptr) { }


HashEntry::HashEntry(Passenger& passenger) :
  status_(OCCUPIED), value_(passenger) { }


HashEntry::~HashEntry() { }



Passenger HashEntry::getValue(void)
{
  return value_;
}


DataStatus HashEntry::getStatus(void)
{
  return status_;
}



void HashEntry::setValue(const Passenger& passenger)
{
  value_ = passenger;
}


void HashEntry::setStatus(const DataStatus& status)
{
  status_ = status;
}



// Public HashTable

HashTable::HashTable
   (
      int initialCapacity, ConsoleTable *linkedTable, double maxLoadFactor = 0.75, 
      std::string& idFieldName = static_cast<std::string> ("passportNumber")
    ) :
  capacity_(initialCapacity), linkedTable_(linkedTable), 
  MAX_LOAD_FACTOR(maxLoadFactor), ID_FIELD_NAME(idFieldName), size_(0) 
{
  for (int i = 0; i < capacity_; i++) {
    data_.push_back(HashEntry());
  }
}


  
double HashTable::getLoadFactor(void) const noexcept
{
    return (size_ / capacity_);
}


int HashTable::getSize(void) const noexcept
{
  return size_;
}


int HashTable::getCapacity(void) const noexcept
{
  return capacity_;
}



bool HashTable::isOccupied(int position)
{
  return (data_.at(position).getStatus() == OCCUPIED);
}


bool HashTable::contains(std::pair<std::string, std::string> &entry)
{
  HashEntry *found = find(entry);
  return (found->getValue.getField(ID_FIELD_NAME) == entry.second);
}


int HashTable::insert(HashEntry& entryToInsert)
{
  int position = 
    findEmptyPosition(entryToInsert.getValue.getField(ID_FIELD_NAME));

  HashEntry* foundEntry = &(data_.at(position));

  if (foundEntry->getStatus != REMOVED) {
    ++size_;
  }

  foundEntry->setStatus(OCCUPIED);
  foundEntry->setValue(entryToInsert.getValue());

  if (getLoadFactor() > MAX_LOAD_FACTOR) {
    rehash();
  }

  delete foundEntry;
  return position;
}


bool HashTable::remove(std::pair<std::string, std::string> &fieldValue)
{
  bool result = false;

  for (auto& e : data_) {
    if (e.getValue().getField(fieldValue.first) == fieldValue.second) {
      result = remove(e);
    }
  }

  return result;
}



void HashTable::displaySearchByPassport(std::string& passportNumber) const
{
  std::pair<std::string, std::string> entry = 
    std::make_pair("passportNumber", passportNumber);

  HashEntry *foundEntry = &(find(entry));

  if (foundEntry == nullptr) {
    std::cout << "Пассажир с номером паспорта '" << passportNumber << "' не найден" << std::endl;
  }
  else {
    system("cls");
    utils::printHeader("ПОИСК ПАССАЖИРА");

    ConsoleTable *tempTable =
      new ConsoleTable{ "Номер паспорта", "Дата выдачи", "ФИО", "Дата рождения" };

    auto rowVector = foundEntry->getValue().getVector();
    tempTable->addRow(rowVector);

    std::cout << *tempTable;

    delete tempTable;
  }
  delete foundEntry;
}


void HashTable::displaySearchByName(std::string& name) const
{
  std::transform(name.begin(), name.end(), name.begin(), ::toupper);

  std::vector<HashEntry> searchResults;

  for (auto entry : data_) {
    std::string currentEntryName = entry.getValue().getField("fullName");
    std::transform(currentEntryName.begin(), currentEntryName.end(), 
                   currentEntryName.begin(), ::toupper);

    if (currentEntryName.find(name) != std::string::npos) {
      searchResults.push_back(entry);
    }
  }

  if (searchResults.empty()) {
    utils::printHeader("Пассажиры по запросу '" + name + "' не найдены");
  }
  else {
    system("cls");
    utils::printHeader("ПОИСК ПАССАЖИРОВ");

    ConsoleTable *tempTable =
      new ConsoleTable{ "Номер паспорта", "Дата выдачи", "ФИО", "Дата рождения" };

    for (auto entry : searchResults) {
      auto rowVector = entry.getValue().getVector();
      tempTable->addRow(rowVector);
    }

    std::cout << *tempTable;
    delete tempTable;
  }
}



HashEntry *HashTable::find(std::pair<std::string, std::string>& field)
{
  int position = findPosition(field.second);

  if (position < 0 || position > capacity_) {
    return nullptr;
  }

  HashEntry* foundEntry = &(data_.at(position));

  if (foundEntry->getValue().getField(field.first) == field.second) {
    return foundEntry;
  } 
  else {
    return nullptr;
  }
}



// Private HashTable

size_t HashTable::hashCode(const std::string& element) const
{
  return (std::hash<std::string>()(element) % capacity_);
}


int HashTable::findEmptyPosition(const std::string& id)
{
  int collisions = 0;
  int currentPosition = hashCode(id);

  while (data_.at(currentPosition).getStatus() != EMPTY) {
    currentPosition = currentPosition + 2 * ++collisions - 1;

    if (currentPosition > capacity_) {
      currentPosition -= capacity_;
    }
  }

  return currentPosition;
}


int HashTable::findPosition(const std::string& id)
{
  int currentPosition = hashCode(id);
  int collisions = 0;

  while (data_.at(currentPosition).getStatus() != OCCUPIED) {
    currentPosition = currentPosition + 2 * ++collisions - 1;

    if (currentPosition > capacity_ - 1) {
      currentPosition -= capacity_;
    }
    if (collisions > capacity_ - 1) {
      return -1;
    }
  }

  return currentPosition;
}


bool HashTable::remove(HashEntry& entryToRemove)
{
  int position =
    findPosition(entryToRemove.getValue().getField(ID_FIELD_NAME));

  HashEntry* foundEntry = &(data_.at(position));

  if (foundEntry->getStatus() != OCCUPIED) {
    delete foundEntry;
    return false;
  }

  if (foundEntry->getValue().getField(ID_FIELD_NAME) ==
      entryToRemove.getValue().getField(ID_FIELD_NAME)) {

    foundEntry->setStatus(REMOVED);
    size_--;
    linkedTable_->remove(foundEntry->getValue().getField(ID_FIELD_NAME));

    delete foundEntry;
    return true;
  }

  delete foundEntry;
  return false;
}


void HashTable::rehash(void)
{
  std::vector<HashEntry> oldVector = data_;
  data_.resize(2 * oldVector.size());

  for (auto& hashEntry : data_) {
    hashEntry.setStatus(EMPTY);
  }

  size_ = 0;

  for (auto& hashEntry : oldVector) {
    if (hashEntry.getStatus() == OCCUPIED) {
      insert(hashEntry);
    }
  }
}



HashEntry *HashTable::searchByPassport(std::string passportNumber)
{
  std::pair<std::string, std::string> toFind =
    std::make_pair("passportNumber", passportNumber);

  return find(toFind);
}



//std::vector<std::string> HashTable::getCollisions(std::string s) {
//  std::vector<std::string> collisions;
//  int goal = hashCode(s);
//  int count = 0;
//    for (int i = 0; i < 9; i++) {
//      std::string firstPart = "400" + std::to_string(i) + "0-";
//      for (int j = 0; j < 1000000; j++) {
//        std::string secondPart = std::to_string(j);
//        while (secondPart.size() != 6)
//          secondPart = "0" + secondPart;
//        if (goal == hashCode(firstPart + secondPart)) {
//          collisions.push_back(firstPart + secondPart);
//          std::cout << "FOUND " << firstPart + secondPart << std::endl;
//          count++;
//        }
//        if (count > 10)
//          return collisions;
//      }
// 
//    std::cout << "400" << std::to_string(i) << "- out" << std::endl;
//  }
//    return collisions;
//}
