#include <array>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>

#include "AVLTree.h"
#include "DoublyLinkedList.h"
#include "Flight.h"
#include "HashTable.h"
#include "Passenger.h"
#include "Ticket.h"

using namespace std;

HashTable passengers(32);
AVLTree *airFlights = new AVLTree();
DoublyLinkedList *tickets = new DoublyLinkedList();

const array<string, 16> MESSAGES = {  };

template <class T>
void displayTable(T dataStructure) {
  ;
}

void addPassenger(string);
void addAirFlight(string, int *);
void addTicket(string);

int main(int argc, char *argv[]) {
  for (int i = 0; i < 79; i++) {
    //addPassenger("1234-567890," + to_string(i) + ",Mad Max,01/01/1970");
    //int ip[2] = { 228, 69 };
    //int f = ((i * 100 + i * 10 + i) % 1000);
    //addAirFlight(to_string(f) + "-" + to_string(f / 2) + ",Pidorashka Avia,PLK,DOM,28/05,17:30", ip);
  }
  addTicket("1234-567890,AVL-305,228691488");
 // passengers.display();
  //airFlights->display();
  tickets->display();
  system("pause"); 
  return 0;
}

void addPassenger(string x) {
  string s[4];
  for (int i = 0; i < 3; i++) {
    int pos = x.find(',');
    if (pos == string::npos)
      throw exception("Неверный формат входного файла");
    s[i] = x.substr(0, pos);
    x = x.substr(pos + 1);
  } 
  s[3] = x;
  try {
    Passenger passenger(s);
    passengers.insert(HashEntry(passenger));
  } catch (exception &e) {
    cerr << e.what();
  }
}

void addAirFlight(string x, int *ip) {
  string stringParameters[6];
  int intParameters[2];
  for (int i = 0; i < 5; i++) {
    int pos = x.find(',');
    if (pos == string::npos)
      throw exception("Неверный формат входного файла");
    stringParameters[i] = x.substr(0, pos);
    x = x.substr(pos + 1);
  }
  stringParameters[5] = x;

  intParameters[0] = (int) ip[0];
  intParameters[1] = (int) ip[1];

  const Flight airFlight(stringParameters, intParameters);
  airFlights->insert(airFlight);
}

void addTicket(string x) {
  string stringParameters[3];
  for (int i = 0; i < 2; i++) {
    int pos = x.find(',');
    if (pos == string::npos)
      throw exception("Неверный формат входного файла");
    stringParameters[i] = x.substr(0, pos);
    x = x.substr(pos + 1);
  }
  stringParameters[2] = x;
  Ticket _t1(stringParameters, SOLD);
  tickets->pushBack(_t1);
  Ticket _t2(stringParameters, RETURNED);
  tickets->pushBack(_t2);
}
