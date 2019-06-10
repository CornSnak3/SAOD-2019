#include <array>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <iomanip>
#include <iostream>
#include <random> 
#include <string>
#include <vector>

#include "AVLTree.h"
#include "ConsoleTable.h"
#include "DoublyLinkedList.h"
#include "Flight.h"
#include "HashTable.h"
#include "Passenger.h"
#include "Ticket.h"

using namespace std;

ConsoleTable *passengersTable = new ConsoleTable{
  "Номер паспорта", "Дата выдачи", "ФИО", "Дата рождения" };

HashTable *passengers = new HashTable(32, passengersTable);
AVLTree *flights = new AVLTree();
DoublyLinkedList *tickets = new DoublyLinkedList();



int passengerTotal = 0;
int flightTotal = 0;
int ticketTotal = 0;

//void addPassenger();
//void deletePassenger();
//void showAllPassengers();
//void searchPassengerByName();
void searchPassengerByPassport();
//
//void addFlight();
//void deleteFlight();
//void deleteAllFlights();
//void searchFlightByAirport();
//void searchFlightByNumber();
//void showAllFlights();
//
//void addTicket(const Passenger &, Flight &);
//void addTicket();
//void returnTicket();
//void showAllTickets();
//
int inputint() {
  int x;
  do {
    cin.ignore(cin.rdbuf()->in_avail());
    cin >> x;
  } while (cin.fail());
  return x;
}

int main(int argc, char *argv[]) {
  std::mt19937 gen;
  gen.seed(time(0));
  setlocale(LC_ALL, "Russian");
  //int menu = 1;
  //while (menu) {
  //  system("cls");
  //  cout << "1 PASSENGERS" << endl << "2 FLIGHTS" << endl << "3 TICKETS" << endl
  //    << "4 TEST" << endl << "0 EXIT" << endl << ">> ";
  //  menu = inputint();
  //  if (menu == 0)
  //    break;
  //  else if (menu == 1) { // Пассажиры
  //    int submenu = 1;
  //    while (submenu) {
  //      system("cls");
  //      cout << "1 ADD PASSENGER" << endl;
  //      if (passengerTotal > 0)
  //        cout << "2 DELETE PASSENGER" << endl << "3 SHOW ALL PASSENGERS" << endl <<
  //        "4 SEARCH PASSENGER BY FULL NAME" << endl << "5 SEARCH PASSENGER BY PASSPORT" << endl;
  //      cout << "0 BACK" << endl << ">> ";
  //      submenu = inputint();
  //      if (submenu == 0)
  //        break;
  //      else if (submenu == 1)
  //        addPassenger();
  //      else if (submenu == 2 && passengerTotal > 0)
  //        deletePassenger();
  //      else if (submenu == 3 && passengerTotal > 0)
  //        showAllPassengers();
  //      else if (submenu == 4 && passengerTotal > 0)
  //        searchPassengerByName();
  //      else if (submenu == 5 && passengerTotal > 0)
  //        searchPassengerByPassport();
  //    }
  //  } else if (menu == 2) { // Авиарейсы
  //    int submenu = 1;
  //    while (submenu) {
  //      system("cls");
  //      cout << "1 ADD FLIGHT " << endl;
  //      if (flightTotal > 0)
  //        cout << "2 DELETE FLIGHT" << endl << "3 SHOW ALL FLIGHTS" <<  endl 
  //        << "4 SEARCH FLIGHT BY NUMBER" << endl << "5 SEARCH FLIGHT BY AIRPORT" << endl;
  //      std::cout << "0 BACK" << std::endl << ">> ";
  //      submenu = inputint();
  //      if (submenu == 0)
  //        break;
  //      else if (submenu == 1)
  //        addFlight();
  //      else if (submenu == 2 && flightTotal > 0)
  //        deleteFlight();
  //      else if (submenu == 3 && flightTotal > 0)
  //        showAllFlights();
  //      else if (submenu == 4 && flightTotal > 0)
  //        searchFlightByNumber();
  //      else if (submenu == 5 && flightTotal > 0)
  //        searchFlightByAirport();
  //    }
  //  }
  //  else if (menu == 3) { // Билеты
  //    int submenu = 1;
  //    while (submenu) {
  //      system("cls");
  //      cout << "1 ADD TICKET" << endl;
  //      if (ticketTotal > 0)
  //        cout << "2 RETURN TICKET" << endl << "3 SHOW ALL TICKETS" << endl;
  //      cout << "0 BACK" << endl << ">> ";
  //      submenu = inputint();
  //      if (submenu == 0)
  //        break;
  //      else if (submenu == 1)
  //        addTicket();
  //      else if (submenu == 2 && ticketTotal > 0)
  //        returnTicket();
  //      else if (submenu == 3 && ticketTotal > 0)
  //        showAllTickets();
  //    }
  //  } else if (menu == 4) {
      std::initializer_list<std::string> testPassengerList =
        { "4009-846396", "20.09.2009", "Волков Леонид Дмитриевич", "31.08.1995" };
      Passenger leonid(testPassengerList);
      passengersTable->addRow(leonid.getVector());
      passengers->insert(leonid);
      cout << *passengersTable;
      system("pause");
      passengers->displaySearchByPassport("4009-846396");
      system("pause");
      //}
  //}
}

//void addPassenger() {
//  string s[4];
//  string queries[] = { "PASSPORT NUMBER", "PASSPORT ISSUED", "FULL NAME", "BIRTHDAY DATE" };
//  for (int i = 0; i < 4; i++) {
//    cin.ignore(cin.rdbuf()->in_avail());
//    cout << setw(25) << left << queries[i];
//    getline(cin, s[i]);
//  }
//  try {
//    Passenger passenger(s);
//    passengers->insert(HashEntry(passenger));
//    system("cls");
//    passengerTotal++;
//    passengers->display();
//  } catch (invalid_argument e) {
//    cout << e.what();
//  }
//  system("pause");
//}

//void deletePassenger() {
//  system("cls");
//  passengers->display();
//  string s;
//  cout <<  "DELETE PASSENGER" << endl << setw(25) << "PASSPORT NUMBER";
//  cin.ignore(cin.rdbuf()->in_avail());
//  getline(cin, s);
//  if (passengers->remove(s)) {
//    passengerTotal--;
//    cout << "PASSENGER REMOVED" << endl;
//
//  } else  
//    cout << "PASSENGER NOT FOUND" << endl;
//  system("pause");
//}

void showAllPassengers() {
  system("cls");
  cout << *passengersTable;
  system("pause");
}

//void searchPassengerByName() {
//  system("cls");
//  string s;
//  cout << setw(25) << left << "PASSPORT NUMBER";
//  cin.ignore(cin.rdbuf()->in_avail());
//  getline(cin, s);
//  passengers->displaySearchByName(s);
//  system("pause");
//}

void searchPassengerByPassport() {
  system("cls");
  string s;
  cout << setw(25) << left << "PASSPORT NUMBER";
  cin.ignore(cin.rdbuf()->in_avail());
  getline(cin, s);
  passengers->displaySearchByPassport(s);
  system("pause");
}

//void addFlight() {
//  string sParams[7];
//  string queries[] = { "FLIGHT NUMBER", "COMPANY", "DEPARTURE AIRPORT", "ARRIVAL AIRPORT",
//    "DEPARTURE DATE", "DEPARTURE TIME", "TOTAL SEATS" };
//  for (int i = 0; i < 7; i++) {
//    cin.ignore(cin.rdbuf()->in_avail());
//    cout << setw(25) << left << queries[i];
//    getline(cin, sParams[i]);
//  }
//  Flight flight(sParams);
//  flights->insert(flight);
//  system("cls");
//  flights->display();
//  flightTotal++;
//  system("pause");
//}
//
//void deleteFlight() {
//  system("cls");
//  flights->display();
//  string s;
//  cout << "DELETE FLIGHT" << endl << setw(25) << left << "FLIGHT NUMBER";
//  cin.ignore(cin.rdbuf()->in_avail());
//  getline(cin, s);
//  if (flights->remove(s)) {
//    flightTotal--;
//    cout << "FLIGHT REMOVED" << endl;
//  } else
//    cout << "FLIGHT NOT FOUND" << endl;
//  system("pause");
//}
//
//void searchFlightByAirport() {
//  system("cls");
//  string s;
//  cout << "FIND FLIGHT BY DEPARTURE AIRPORT" << endl << setw(25) << left << "PATTERN";
//  cin.ignore(cin.rdbuf()->in_avail());
//  getline(cin, s);
//  vector<Flight> *selection = flights->searchByPattern(s);
//  system("cls");
//  cout << "SEARCH RESULTS FOR PATTERN \"" << s << "\"" << endl;
//  cout << setw(15) << left << "FLIGHT NUMBER" << setw(20) << left << "COMPANY" <<
//    setw(25) << left << "DEPARTURE" << setw(25) << left << "ARRIVAL" << setw(10) <<
//    left << "DATE" << setw(10) << left << "TIME" << setw(10) << left << "SEATS" <<
//    setw(10) << left << "FREE SEATS" << endl;
//  for (auto &flight : *selection)
//    cout << flight;
//  system("pause");
//}
//
//void searchFlightByNumber() {
//  system("cls");
//  string s;
//  cout << "FIND FLIGHT BY FLIGHT NUMBER" << endl << setw(25) << left << "PATTERN";
//  cin.ignore(cin.rdbuf()->in_avail());
//  getline(cin, s);
//  system("cls");
//  cout << "SEARCH RESULTS FOR NUMBER " << s  << endl;
//  cout << setw(15) << left << "FLIGHT NUMBER" << setw(20) << left << "COMPANY" <<
//    setw(25) << left << "DEPARTURE" << setw(25) << left << "ARRIVAL" << setw(10) <<
//    left << "DATE" << setw(10) << left << "TIME" << setw(10) << left << "SEATS" <<
//    setw(10) << left << "FREE SEATS" << endl;
//  if (!flights->searchByNumber(s))
//    cout << "FLIGHT NOT FOUND" << endl;
//  system("pause");
//}
//
//void showAllFlights() {
//  system("cls");
//  flights->display();
//  system("pause");
//}

//void addTicket(const Passenger &p, Flight &f) {
//  string s[] = { p.getNumber(), f.getFlightNumber(), tickets->getNextTicketNumber() };
//  Ticket ticket(s, SOLD);
//  tickets->pushBack(ticket);
//  ticketTotal++;
//  f.sellTicket();
//}

//void addTicket() {
//  system("cls");
//  string s[3];
//  cout << "SELL TICKET" << endl << setw(25) << left << "PASSPORT NUMBER";
//  cin.ignore(cin.rdbuf()->in_avail());
//  getline(cin, s[0]);
//  if (!passengers->contains(s[0])) {
//    cout << "NO PASSENGER WITH THIS PASSPORT NUMBER EXISTS" << endl;
//  } else {
//    cout << setw(25) << left << "FLIGHT NUMBER";
//    cin.ignore(cin.rdbuf()->in_avail());
//    getline(cin, s[1]);
//    if (!flights->isTicketAvailible(s[1]))
//      cout << "NO FLIGHT WITH THIS NUMBER EXISTS" << endl;
//    else {
//      s[2] = tickets->getNextTicketNumber();
//      Ticket ticket(s, SOLD);
//      tickets->pushBack(ticket);
//    }
//  }   
//  ticketTotal++;
//  system("pause");
//}

//void removeTicketByFlight(string flightNumber) {
//  for (int i = 0; i < tickets->getSize(); i++) {
//    if (tickets->att(i).getFlightNumber() == flightNumber)
//      tickets->remove(i);
//  }
//}
//
//void returnTicket() {
//  system("cls");
//  tickets->display();
//  string s;
//  cout << "RETURN TICKET" << endl << setw(25) << "NUMBER";
//  cin.ignore(cin.rdbuf()->in_avail());
//  getline(cin, s);
//  if (tickets->returnTicket(s)) {
//    ticketTotal--;
//    cout << "TICKET RETURNED" << endl;
//  }
//  else
//    cout << "TICKET NOT FOUND" << endl;
//  system("pause");
//}
//
//void showAllTickets() {
//  system("cls");
//  tickets->display();
//  system("pause");
//}