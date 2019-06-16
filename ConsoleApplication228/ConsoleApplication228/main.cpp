#include <array>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <iomanip>
#include <iostream>
#include <locale>
#include <random> 
#include <string>
#include <vector>
#include <Windows.h>

#include "AVLTree.h"
#include "ConsoleTable.h"
#include "DoublyLinkedList.h"
#include "Flight.h"
#include "HashTable.h"
#include "Passenger.h"
#include "Ticket.h"
#include "Utils.h"

using namespace std;

// Счетчики
int totalPassengers = 0;
int totalFlights    = 0;
int totalTickets    = 0;

// Структуры пассажиров
ConsoleTable *passengersTable = new ConsoleTable {
  "Номер паспорта", "Дата выдачи", "ФИО", "Дата рождения"
};

HashTable *passengers = new HashTable(32, passengersTable, 0.75,
                                      static_cast<string> ("passportNumber"));

// Структуры авиарейсов
ConsoleTable *flightsTable = new ConsoleTable {
  "Номер рейса", "Авиакомпания", "Отправление", "Прибытие", "Время вылета",
  "Всего мест", "Свободно мест"
};

AVLTree *flights = new AVLTree(flightsTable);


// Структуры билетов
ConsoleTable *ticketsTable = new ConsoleTable{
  "Номер билета", "Номер паспорта пассажира", "Номер рейса", "Статус"
};

DoublyLinkedList* tickets = new DoublyLinkedList();


// Функции работы с пассажирами
void newPassenger              (void);
void deletePassenger           (void);
void showAllPassengers         (void);
void searchPassengerByName     (void);
void searchPassengerByPassport (void);


// Функции работы с рейсами
void newFlight();
//void deleteFlight();
//void deleteAllFlights();
//void searchFlightByAirport();
//void searchFlightByNumber();
//void showAllFlights();


// Функции работы с билетами
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


// Элементы меню

void executeMenu(void);

vector<string> mainMenu = {
  "ГЛАВНОЕ МЕНЮ", "Пассажиры", "Рейсы", "Билеты", "Тест" 
};

vector<string> passengersMenu = {
  "ПАССАЖИРЫ", "Добавить", "Удалить", "Список", "Поиск по паспорту", "Поиск по имени" 
};

vector<string> flightsMenu = { 
  "РЕЙСЫ", "Добавить", "Удалить", "Список", "Поиск по аэропорту"
};

vector<string> ticketsMenu = {
  "БИЛЕТЫ", "Покупка", "Возврат", "Список"
};


int main(int argc, char *argv[])
{
  setlocale(LC_ALL, "Russian");
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  
  // Main

  executeMenu();

  return 0;
}


// Menu

void executeMenu(void)
{
  while (true) {

    system("cls");

    switch (utils::executeMenu(mainMenu)) 
    {
      case -1:
        return;

      case 0:
        switch (utils::executeMenu(passengersMenu)) // Меню пассажиров
        { 
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

      // Меню рейсов
      case 1:
        switch (utils::executeMenu(flightsMenu))
        {      
          case -1:
            break;
      
          case 0:
            newFlight();
            break;
      
          case 1:
            cout << *flightsTable;
            //deleteFlight();
            break;
      
          case 2:
            cout << *flightsTable;
            system("pause");
            break;
      
          case 3:
            std::cout << setw(25) << left << "Название или его часть" << ">> ";
            string s;
            cin.ignore(cin.rdbuf()->in_avail());
            getline(cin, s);
            flights->displaySearchByPattern(s);
            break;
      }

      break;

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
}


// Test

void test(void)
{
  system("cls");

  cout << "Вывод таблицы пассажиров с тестовыми записями" << endl; 

  // Инициализация пассажиров

  vector<initializer_list<string>> testPassengersInitializers;


  initializer_list<string> testPassenger1InitializerList = {
    "4009-846396", "20.09.2009", "Волков Леонид Дмитриевич", "31.08.1995" 
  };
  testPassengersInitializers.push_back(testPassenger1InitializerList);


  initializer_list<string> testPassenger2InitializerList = { 
    "4000-000023", "12.11.2002", "Волков Дмитрий Анатольевич", "17.09.1967"
  };
  testPassengersInitializers.push_back(testPassenger2InitializerList);


  initializer_list<string> testPassenger3InitializerList = { 
    "4000-000056", "03.02.2000", "Волкова Ольга Викторовна", "11.03.1967"
  };
  testPassengersInitializers.push_back(testPassenger3InitializerList);


  initializer_list<string> testPassenger4InitializerList = {
    "4000-000131", "08.05.2012", "Зуевская Екатерина Игоревна", "07.05.1998"
  };
  testPassengersInitializers.push_back(testPassenger4InitializerList);


  initializer_list<string> testPassenger5InitializerList = {
    "3810-556131", "25.04.1992", "Кобейн  Дональд Курт", "20.02.1967"
  };
  testPassengersInitializers.push_back(testPassenger5InitializerList);


  initializer_list<string> testPassenger6InitializerList = {
    "2536-887544", "01.12.1979", "Кертис Кевин Иэн", "15.06.1956"
  };
  testPassengersInitializers.push_back(testPassenger6InitializerList);


  initializer_list<string> testPassenger7InitializerList = {
    "3999-278045", "22.08.1999", "Лейн Томас Стэйли", "22.08.1967"
  };
  testPassengersInitializers.push_back(testPassenger7InitializerList);
 

  for (auto& i : testPassengersInitializers) {
    Passenger newPassenger(i);
    passengers->insert(HashEntry(newPassenger));
    passengersTable->addRow(newPassenger.getVector());
  }

  cout << *passengersTable;
  system("pause");

  cout << endl << "Удаление записи, имеющей коллизии в хэш-таблице" << endl;

  pair<string, string> passengerToRemove = 
    make_pair("passportNumber", "4000-000056");
  passengers->remove(passengerToRemove);

  cout << *passengersTable;
  system("pause");

  
  // Тест рейсов
  
  

  initializer_list<string> testFlight2InitList = {
    "000-004", "S7 Airlines", "Москва Домодедово DME",
    "Сочи Адлер AER", "11 Июня, 20:10", "144", "144" 
  };

  Flight testFlight2(testFlight2InitList);
  flights->insert(testFlight2);
  flightsTable->addRow(testFlight2.getVector());


  initializer_list<string> testFlight3InitList ={ 
    "000-001", "Белаваиа", "Санкт-Петербург Пулково LED",
    "Минск Минск-2 MSQ", "11 Июня, 20:05", "120", "120"
  };

  Flight testFlight3(testFlight3InitList);
  flights->insert(testFlight3);
  flightsTable->addRow(testFlight3.getVector());


  initializer_list<string> testFlight4InitList =
  { "000-002", "Tokio Air", "Санкт-Петербург Пулково LED",
    "Токио Ханеда HND", "11 Июня, 18:05", "174", "174"
  };

  Flight testFlight4(testFlight4InitList);
  flights->insert(testFlight4);
  flightsTable->addRow(testFlight4.getVector());

  initializer_list<string> testFlight5InitList = {
    "000-003", "Аэрофлот", "Санкт-Петербург Пулково LED",
    "Ханой Нанбай HAN", "12 Июня, 17:30", "100", "100"
  };

  Flight testFlight5(testFlight5InitList);
  flights->insert(testFlight5);
  flightsTable->addRow(testFlight5.getVector());

  initializer_list<string> testFlight1InitList = { 
    "000-005", "Аэрофлот", "Москва Шереметьево SVO",
    "Санкт-Петербург Пулково LED", "11 Июня, 03:45", "180", "180"
  };


  Flight testFlight1(testFlight1InitList);
  flights->insert(testFlight1);
  flightsTable->addRow(testFlight1.getVector());

  system("cls");

  flightsTable->removeAll();
  flights->addPostOrder();


  cout << *flightsTable;

  system("pause");

  flights->removeRoot();

  cout << *flightsTable;

  system("pause");

  flights->displaySearchByPattern(static_cast<string>("улков"));
  system("pause");

  flights->displaySearchByPattern(static_cast<string>("одед"));
  system("pause");



  flights->displaySearchByPattern(static_cast<string>("о LED"));
  system("pause");

  cout << *flightsTable;
  system("pause");



}


void newPassenger(void) {
  utils::printHeader("НОВЫЙ ПАССАЖИР");
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
    passengers->insert(HashEntry(passenger));
    passengersTable->addRow(passenger.getVector());
    showAllPassengers();
    system("pause");
  } catch (...) {
    return;
  }
}

void deletePassenger(void) {
  utils::printHeader("УДАЛИТЬ ПАССАЖИРА");
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

void newFlight() {
  string s[7];
  string queries[] = { "FLIGHT NUMBER", "COMPANY", "DEPARTURE AIRPORT", "ARRIVAL AIRPORT",
    "DEPARTURE DATE", "DEPARTURE TIME", "TOTAL SEATS" };
  for (int i = 0; i < 7; i++) {
    cin.ignore(cin.rdbuf()->in_avail());
    cout << setw(25) << left << queries[i];
    getline(cin, s[i]);
  }
  initializer_list<string> flightInitList = { s[0], s[1], s[2], s[3], s[4], s[5], s[6] };
  Flight flight(flightInitList);
  flights->insert(flight);
  cout << *flightsTable;
  totalFlights++;
  system("pause");
}
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