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
#include "Utils.h"

using namespace std;

ConsoleTable *passengersTable = new ConsoleTable{
  "Номер паспорта", "Дата выдачи", "ФИО", "Дата рождения" };

ConsoleTable *flightsTable = new ConsoleTable{
  "Номер рейса", "Авиакомпания", "Отправление", "Прибытие",
  "Время вылета", "Всего мест", "Свободно мест" };

HashTable *passengers = new HashTable(32, passengersTable);
AVLTree *flights = new AVLTree(flightsTable);
DoublyLinkedList *tickets = new DoublyLinkedList();



int passengerTotal = 0;
int flightTotal = 0;
int ticketTotal = 0;

void newPassenger(void);
void deletePassenger(void);
void showAllPassengers(void);
void searchPassengerByName(void);
void searchPassengerByPassport(void);
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

void test(void);

int inputint(void) {
  int x;
  do {
    cin.ignore(cin.rdbuf()->in_avail());
    cin >> x;
  } while (cin.fail());
  return x;
}

vector<string> mainMenu = 
{ "ГЛАВНОЕ МЕНЮ", "Пассажиры", "Рейсы", "Билеты", "Тест" };

vector<string> passengersMenu = 
{ "ПАССАЖИРЫ", "Добавить", "Удалить", "Список", "Поиск по паспорту", "Поиск по имени" };

vector<string> flightsMenu =
{ "РЕЙСЫ", "Добавить", "Удалить", "Список", "Поиск по аэропорту" };

vector<string> ticketsMenu = 
{ "БИЛЕТЫ", "Покупка", "Возврат", "Список" };


int main(int argc, char *argv[]) {

  setlocale(LC_ALL, "Russian");

  int menu = 1;
  while (menu) {
    system("cls");
    switch (Utils::executeMenu(mainMenu)) {

    case -1: 
      return 0;

    case 0:
      switch (Utils::executeMenu(passengersMenu)) { // Меню пассажиров
      case -1:
        break;
      case 0: 
        newPassenger();
        break;
      case 1:
        if (passengers->getSize() > 0) {
          showAllPassengers();
          deletePassenger();
        }
        break;
      case 2:
        showAllPassengers();
        system("pause");
        break;
      case 3:
        searchPassengerByPassport();
        break;
      case 4:
        searchPassengerByName();
        break;
      default:
        break;
      }
      break;

    //case 1:
    //  switch (Utils::executeMenu(flightsMenu)) { // Меню рейсов
    //  case -1:
    //    break;
    //  case 0:
    //    newFlight();
    //    break;
    //  case 1:
    //    showAllFlights();
    //    deleteFlight();
    //    break;
    //  case 2:
    //    showAllFlights();
    //    system("pause");
    //    break;
    //  case 3:
    //    searchFlightByAirport();
    //    break;
    //  default:
    //    break;
    //  }
    //  break;

    //case 2:
    //  switch (Utils::executeMenu(flightsMenu)) { // Меню билетов

    //  case -1:
    //    break;
    //  case 0:
    //    newTicket();
    //    break;
    //  case 1:
    //    returnTicket();
    //    break;
    //  case 2:
    //    showAllTickets();
    //    system("pause");
    //    break;
    //  }

    case 3:
      test();
      break;
    default:
      break;
    }
    
  }
  return 0;
}

void test(void) {
  system("cls");
  initializer_list<string> testPassenger1List =
  { "4009-846396", "20.09.2009", "Volkov Leonid Dmitrievich", "31.08.1995" };
  Passenger testPassenger1(testPassenger1List);
  passengers->insert(testPassenger1);
  passengersTable->addRow(testPassenger1.getVector());

  initializer_list<string> testPassenger2List =
  { "4000-000023", "12.11.2002", "Volkov Dmitry Anatolievich", "17.09.1967" };
  Passenger testPassenger2(testPassenger2List);
  passengers->insert(testPassenger2);
  passengersTable->addRow(testPassenger2.getVector());

  initializer_list<string> testPassenger3List =
  { "4000-000056", "03.02.2000", "Volkova Olga Viktorovna", "11.03.1967" };
  Passenger testPassenger3(testPassenger3List);
  passengers->insert(testPassenger3);
  passengersTable->addRow(testPassenger3.getVector());

  initializer_list<string> testPassenger4List =
  { "4000-000131", "08.05.2012", "Zuevskaya Ekaterina Igorevna", "07.05.1998" };
  Passenger testPassenger4(testPassenger4List);
  passengers->insert(testPassenger4);
  passengersTable->addRow(testPassenger4.getVector());

  cout << *passengersTable;
  system("pause");
  pair<string, string> passToRemove = make_pair("passportNumber", "4000-000056"); // Volkova Olga
  passengers->remove(passToRemove);
  cout << *passengersTable;
  system("pause");

  
  // Тест рейсов
  
  

  initializer_list<string> testFlight2InitList =
  { "000-004", "S7 Airlines", "Moscow Domodedovo DME",
    "Sochi Adler AER", "11 June 20:10", "144", "144" };

  Flight testFlight2(testFlight2InitList);
  flights->insert(testFlight2);
  flightsTable->addRow(testFlight2.getVector());

  initializer_list<string> testFlight3InitList =
  { "000-001", "Belavia", "Sankt-Peterburg Pulkovo LED",
    "Minsk Minsk-2 MSQ", "11 June 20:05", "120", "120" };

  Flight testFlight3(testFlight3InitList);
  flights->insert(testFlight3);
  flightsTable->addRow(testFlight3.getVector());

  initializer_list<string> testFlight4InitList =
  { "000-002", "Tokio Air", "Sankt-Peterburg Pulkovo LED",
    "Tokio Haneda HND", "11 June 18:05", "174", "174" };

  Flight testFlight4(testFlight4InitList);
  flights->insert(testFlight4);
  flightsTable->addRow(testFlight4.getVector());

  initializer_list<string> testFlight5InitList =
  { "000-003", "Saigon Aero", "Sankt-Peterburg Pulkovo LED",
    "Hanoi Nanbai HAN", "12 June 17:30", "100", "100" };

  Flight testFlight5(testFlight5InitList);
  flights->insert(testFlight5);
  flightsTable->addRow(testFlight5.getVector());

  initializer_list<string> testFlight1InitList =
  { "000-005", "Aeroflot", "Sankt-Peterburg Pulkovo LED",
    "Moscow Sherementievo SVO", "11 June 03:45", "180", "180" };


  Flight testFlight1(testFlight1InitList);
  flights->insert(testFlight1);
  flightsTable->addRow(testFlight1.getVector());

  initializer_list<string> testFlight6InitList =
  { "000-006", "Belavia", "Sankt-Peterburg Pulkovo LED",
    "Minsk Minsk-2 MSQ", "11 June 20:05", "120", "120" };

  Flight testFlight6(testFlight6InitList);
  flights->insert(testFlight6);
  flightsTable->addRow(testFlight6.getVector());

  system("pause");

  flightsTable->removeAll();
  flights->addPostOrder();

  cout << *flightsTable;

  system("pause");

  flights->removeRoot();

  cout << *flightsTable;

  system("pause");

  flights->displaySearchByPattern("Pulkov");
  system("pause");

  flights->displaySearchByPattern("oded");
  system("pause");



  flights->displaySearchByPattern("o LED");
  system("pause");

  cout << *flightsTable;
  system("pause");



}


void newPassenger(void) {
  Utils::printHeader("НОВЫЙ ПАССАЖИР");
  string s[4];
  string queries[] = { "НОМЕР ПАСПОРТА", "ДАТА ВЫДАЧИ", "ФИО", "ДАТА РОЖДЕНИЯ" };
  for (int i = 0; i < 4; i++) {
    cin.ignore(cin.rdbuf()->in_avail());
    cout << setw(25) << left << queries[i] << ">> ";
    getline(cin, s[i]);
  }
  initializer_list<string> passengerInitList = { s[0], s[1], s[2], s[3] };
  try {
    Passenger passenger(passengerInitList);
    passengers->insert(passenger);
    passengersTable->addRow(passenger.getVector());
    showAllPassengers();
    system("pause");
  } catch (...) {
    return;
  }
}

void deletePassenger(void) {
  Utils::printHeader("УДАЛИТЬ ПАССАЖИРА");
  cout << setw(25) << left << "НОМЕР ПАСПОРТА" << ">> ";
  string s;
  cin.ignore(cin.rdbuf()->in_avail());
  getline(cin, s);
  pair<string, string> p = make_pair("passportNumber", s);
  if (passengers->remove(p)) 
    cout << "ПАССАЖИР УДАЛЕН" << endl;
  else  
    cout << "ПАССАЖИР НЕ НАЙДЕН" << endl;
  system("pause");
}

void showAllPassengers(void) {
  system("cls");
  cout << *passengersTable;
}

void searchPassengerByName(void) {
  system("cls");
  string s;
  cout << setw(25) << left << "ИМЯ ИЛИ ЧАСТЬ ИМЕНИ" << ">> ";
  cin.ignore(cin.rdbuf()->in_avail());
  getline(cin, s);
  passengers->displaySearchByName(s);
  system("pause");
}

void searchPassengerByPassport(void) {
  system("cls");
  string s;
  cout << setw(25) << left << "НОМЕР ПАСПОРТА" << ">> ";
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