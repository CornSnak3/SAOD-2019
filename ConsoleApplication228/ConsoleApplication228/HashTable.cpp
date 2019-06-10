#include <algorithm>
#include <string> 
#include <Windows.h>

#include "HashTable.h"
#include "Utils.h"

// Public

HashTable::HashTable(int initialCapacity, ConsoleTable *linkedTable) :
  linkedTable(linkedTable), capacity(initialCapacity), size(0) {
  for (int i = 0; i < capacity; i++)
    data.push_back(HashEntry());
}
  
double HashTable::loadFactor(void) const {
    return (size / capacity);
}

bool HashTable::insert(const HashEntry &entry) {
  int currentPosition = findEmptyPosition(entry.value.getField(idFieldName));
  if (data[currentPosition].status != REMOVED)
    ++size;
  data[currentPosition].status = OCCUPIED;
  data[currentPosition].value = entry.value;
  if (loadFactor() > maxLoadFactor)
    rehash();
  return true;
}

HashEntry *HashTable::find(std::pair<std::string, std::string> &fieldValue) {
  int position = findPosition(fieldValue.second);
  if (position < 0 || position > capacity)
    return nullptr;
  if (data.at(position).value.getField(fieldValue.first) == fieldValue.second) {
    HashEntry *returnPtr = &(data.at(position));
    return returnPtr;
  } else {
    return nullptr;
  }
}

bool HashTable::contains(std::pair<std::string, std::string> &entry) {
  HashEntry *found = find(entry);
  return (found->value.getField(idFieldName) == entry.second);
}

void HashTable::displaySearchByPassport(std::string passportNumber) {
  std::pair<std::string, std::string> entry = std::make_pair("passportNumber", passportNumber);
  HashEntry *found = find(entry);
  if (found == nullptr) {
    std::cout << "Ïàññàæèð ñ íîìåðîì ïàñïîðòà '" << passportNumber << "' íå íàéäåí" << std::endl;
  } else {
    system("cls");
    Utils::printHeader("ÏÎÈÑÊ ÏÀÑÑÀÆÈÐÀ");
    ConsoleTable *tempTable =
      new ConsoleTable{ "Íîìåð ïàñïîðòà", "Äàòà âûäà÷è", "ÔÈÎ", "Äàòà ðîæäåíèÿ" };
    auto rowVector = found->value.getVector();
    tempTable->addRow(rowVector);
    std::cout << *tempTable;
    delete tempTable;
  }
}

void HashTable::displaySearchByName(std::string name) {
  std::string temp(name);
  std::vector<HashEntry> searchResults;
  std::transform(name.begin(), name.end(), name.begin(), ::tolower);
  for (auto entry : data) {
    std::string currentEntry = entry.value.getField("fullName");
    std::transform(currentEntry.begin(), currentEntry.end(), currentEntry.begin(), ::tolower);
    if (currentEntry == name)
      searchResults.push_back(entry);
  }
  if (searchResults.empty()) {
    Utils::printHeader("ÏÀÑÑÀÆÈÐÛ ÏÎ ÇÀÏÐÎÑÓ '" + temp + "' ÍÅ ÍÀÉÄÅÍ");
  } else {
    system("cls");
    Utils::printHeader("ÏÎÈÑÊ ÏÀÑÑÀÆÈÐÎÂ");
    ConsoleTable *tempTable =
      new ConsoleTable{ "Íîìåð ïàñïîðòà", "Äàòà âûäà÷è", "ÔÈÎ", "Äàòà ðîæäåíèÿ" };
    for (auto entry : searchResults) {
      auto rowVector = entry.value.getVector();
      tempTable->addRow(rowVector);
    }
    std::cout << *tempTable;
    delete tempTable;
  }
}

bool HashTable::isOccupied(int currentPosition) const {
  return (data.at(currentPosition).status == OCCUPIED);
}

bool HashTable::remove(std::pair<std::string, std::string> &fieldValue) {
  bool flag = false;
  for (auto &e : data) {
    if (e.value.getField(fieldValue.first) == fieldValue.second)
      flag = remove(e);
  }
  return flag;
}
 
// Private

size_t HashTable::hashCode(const std::string &element) const {
  long long h = 17;
  int x = 31;
  for (const char &c : element) {
    h += c * x;
    x *= x;
  }
  return (h % capacity);
}

HashEntry *HashTable::searchByPassport(std::string passportNumber) {
  std::pair<std::string, std::string> toFind =
    std::make_pair("passportNumber", passportNumber);
  return find(toFind);
}

int HashTable::findEmptyPosition(const std::string &id) const {
  int collisions = 0;
  int currentPosition = hashCode(id);
  while (data[currentPosition].status != EMPTY) {
    currentPosition = currentPosition + 2 * ++collisions - 1;
    if (currentPosition > capacity - 1)
      currentPosition -= capacity;
  }
  return currentPosition;
}

int HashTable::findPosition(const std::string &id) {
  int currentPosition = hashCode(id);
  int collisions = 0;
  while (data[currentPosition].status != OCCUPIED) {
    currentPosition = currentPosition + 2 * ++collisions - 1;
    if (currentPosition > capacity - 1)
      currentPosition -= capacity;
    if (collisions > capacity - 1)
      return -1;
  }
  return currentPosition;
}

bool HashTable::remove(const HashEntry &x) {
  int currentPosition = findPosition(x.value.getHashingValue(idFieldName)) - 1;
  if (data[currentPosition].status != OCCUPIED)
    return false;
  if (data[currentPosition].value.getHashingValue(idFieldName) == x.value.getHashingValue(idFieldName)) {
    data[currentPosition].status = REMOVED;
    return true;
  }
  return false;
}

void HashTable::rehash(void) {
  std::vector<HashEntry> oldVector = data;
  data.resize(2 * oldVector.size());
  for (auto & hashEntry : data)
    hashEntry.status = EMPTY;
  size = 0;
  for (auto & hashEntry : oldVector)
    if (hashEntry.status == OCCUPIED)
      insert(hashEntry);
}