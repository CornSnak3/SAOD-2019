#include <array>
#include <cstdlib>
#include <exception>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "AVLTree.h"
#include "DoublyLinkedList.h"
#include "Flight.h"
#include "HashTable.h"
#include "Passenger.h"
#include "Ticket.h"

using namespace std;

HashTable passengers(32);
AVLTree *flights = new AVLTree();
DoublyLinkedList *tickets = new DoublyLinkedList();

int passengerTotal = 0;
int flightTotal = 0;
int ticketTotal = 0;

void addPassenger();
void deletePassenger();
void showAllPassengers();
void searchPassengerByName();
void searchPassengerByPassport();

void addFlight();
void deleteFlight();
void deleteAllFlights();
void searchFlightByAirport();
void searchFlightByNumber();
void showAllFlights();

void addTicket();
void returnTicket();
void showAllTickets();

int inputint() {
  int x;
  cin.clear();
  do {
    cin.ignore(cin.rdbuf()->in_avail());
    cin >> x;
  } while (cin.fail());
  return x;
}

int main(int argc, char *argv[]) {

  int menu = 1;
  while (menu) {
    cout << "1 PASSENGERS" << endl << "2 FLIGHTS" << endl << "3 TICKETS" << endl << "0 EXIT" << endl << ">> ";
    menu = inputint();
    if (menu == 0)
      break;
    else if (menu == 1) { // Пассажиры
      int submenu = 1;
      while (submenu) {
        system("CLS");
        cout << "1 ADD PASSENGER" << endl;
        if (passengerTotal > 0)
          cout << "2 DELETE PASSENGER" << endl << "3 SHOW ALL PASSENGERS" << endl <<
          "4 SEARCH PASSENGER BY FULL NAME" << endl << "5 SEARCH PASSENGER BY PASSPORT" << endl;
        cout << "0 BACK" << endl << ">> ";
        submenu = inputint();
        if (submenu == 0)
          break;
        else if (submenu == 1)
          addPassenger();
        else if (submenu == 2 && passengerTotal > 0)
          deletePassenger();
        else if (submenu == 3 && passengerTotal > 0)
          showAllPassengers();
        else if (submenu == 4 && passengerTotal > 0)
          searchPassengerByName();
        else if (submenu == 5 && passengerTotal > 0)
          searchPassengerByPassport();
      }
    }
    else if (menu == 2) { // Авиарейсы
      int submenu = 1;
      while (submenu) {
        system("CLS");
        cout << "1 ADD FLIGHT " << endl;
        if (flightTotal > 0)
          cout << "2 DELETE FLIGHT" << endl << "3 SHOW ALL FLIGHTS" << endl
          << "4 DELETE ALL FLIGHTS" << endl << "5 SEARCH FLIGHT BY NUMBER" << endl
          << "6 SEARCH FLIGHT BY AIRPORT" << endl;
        std::cout << "0 BACK" << std::endl << ">> ";
        submenu = inputint();
        if (submenu == 0)
          break;
        else if (submenu == 1)
          addFlight();
        else if (submenu == 2 && flightTotal > 0)
          deleteFlight();
        else if (submenu == 3 && flightTotal > 0)
          showAllFlights();
        else if (submenu == 4 && flightTotal > 0)
          deleteAllFlights();
        else if (submenu == 5 && flightTotal > 0)
          searchFlightByNumber();
        else if (submenu == 6 && flightTotal > 0)
          searchFlightByAirport();
      }
    }
    else if (menu == 3 && flightTotal > 0 && passengerTotal > 0) {
      int submenu = 1;
      while (submenu) {
        system("CLS");
        cout << "1 ADD TICKET" << endl;
        if (ticketTotal > 0) {
          cout << "2 RETURN TICKET" << endl << "3 SHOW ALL TICKETS" << endl;
          cout << "0 BACK" << endl << ">> ";
          submenu = inputint();
          if (submenu == 0)
            break;
          else if (submenu == 1)
            addTicket();
          else if (submenu == 2 && ticketTotal > 0)
            returnTicket();
          else if (submenu == 3 && ticketTotal > 0)
            showAllTickets();
        }
      }
    }
  }
}
void addPassenger() {
  string s[4];
  string queries[] = { "PASSPORT NUMBER", "PASSPORT ISSUED", "FULL NAME", "BIRTHDAY DATE" };
  for (int i = 0; i < 4; i++) {
    cin.ignore(cin.rdbuf()->in_avail());
    cout << setw(20) << left << queries[i];
    getline(cin, s[i]);
  }
  Passenger passenger(s);
  passengers.insert(HashEntry(passenger));
  system("cls");
  passengerTotal++;
  passengers.display();
  system("pause");
}

void deletePassenger() {
  system("CLS");
  string s;
  cout <<  "DELETE PASSENGER" << endl << "ENTER PASSPORT NUMBER:";
  cin >> s;
  if (passengers.remove(s)) {
    passengerTotal--;
    cout << "PASSENGER REMOVED" << endl;
  } else  
    cout << "PASSENGER NOT FOUND" << endl;
  system("pause");
}

void showAllPassengers() {
  system("cls");
  passengers.display();
  system("pause");
}

void searchPassengerByName() {

}

void searchPassengerByPassport() {
  system("CLS");
  string s;
  cout << "Enter Passport Number: ";
  getline(cin, s);
  passengers.displaySearchByPassport(s);
  cout << "Press ENTER to return";
  cin.get();
}

void addFlight() {
  string sParams[8];
  string queries[] = { "FLIGHT NUMBER: ", "COMPANY: ", "DEPARTURE AIRPORT: ", "ARRIVAL AIRPORT: ",
    "DEPARTURE DATE: ", "DEPARTURE TIME: ", "TOTAL SEATS: ", "FREE SEATS: " };
  for (int i = 0; i < 8; i++) {
    cin.ignore(cin.rdbuf()->in_avail());
    cout << queries[i];
    getline(cin, sParams[i]);
  }
 
  Flight flight(sParams);
  flights->insert(flight);
  system("cls");
  flights->display();
  flightTotal++;
  system("pause");
}

void deleteFlight() {}

void deleteAllFlights() {}
void searchFlightByAirport() {}
void searchFlightByNumber() {}
void showAllFlights() {}

void addTicket() {}
void returnTicket() {}
void showAllTickets() {}