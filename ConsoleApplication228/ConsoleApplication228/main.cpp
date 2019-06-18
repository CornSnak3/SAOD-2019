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
#include "Menu.h"
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

DoublyLinkedList* tickets = new DoublyLinkedList(ticketsTable);


// Функции работы с пассажирами
void newPassenger              (void);
void deletePassenger           (void);
void showAllPassengers         (void);
void searchPassengerByName     (void);
void searchPassengerByPassport (void);


// Функции работы с рейсами
void newFlight             (void);
void deleteFlight          (void);
void deleteAllFlights      (void);
void searchFlightByAirport (void);
void searchFlightByNumber  (void);
void showAllFlights        (void);


// Функции работы с билетами
void newTicket             (void);
void returnTicket          (void);
void deleteTicketsOnFlight (void);
void showAllTickets        (void);


// Демо
void demo(void);


// Элементы меню

void executeMenu(void);

initializer_list<string> mainMenuInitializerList       = {
  "ПРОДАЖА АВИАБИЛЕТОВ", "Пассажиры ", "Авиарейсы ", "Билеты    ", "Демо      " 
};

initializer_list<string> passengersMenuInitializerList = {
  "ПАССАЖИРЫ", "Добавить пассажира", "Удалить пассажира", "Список пассажиров", "Поиск по паспорту ", "Поиск по имени   " 
};

initializer_list<string> flightsMenuInitializerList    = { 
  "АВИАРЕЙСЫ", "Добавить авиарейс    ", "Удалить авиарейс     ",
  "Список авиарейсов    ", "Поиск по аэропорту   ", "Поиск по номеру рейса"
};

initializer_list<string> ticketsMenuInitialierList     = {
  "БИЛЕТЫ", "Покупка билета", "Возврат билета", "Список билетов"
};



int main(int argc, char *argv[])
{
  setlocale(LC_ALL, "Russian");
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  
  // Main sequence
  executeMenu();

  return 0;
}


// Menu
void executeMenu(void)
{
  while (true) {

    system("cls");
    
    Menu mainMenu      (mainMenuInitializerList);
    Menu passengerMenu (passengersMenuInitializerList);
    Menu flightsMenu   (flightsMenuInitializerList);
    Menu ticketsMenu   (ticketsMenuInitialierList);

    switch (mainMenu.execute()) 
    {
      // ESC
      case -1:
        return;

      // Меню пассажиров
      case 0:
        switch (passengerMenu.execute())
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
            if (passengers->getSize() > 0) {
              showAllPassengers();
              system("pause");
            }
            break;
      
          case 3:
            if (passengers->getSize() > 0) {
              searchPassengerByPassport();
            }
            break;
      
          case 4:
            if (passengers->getSize() > 0) {
              searchPassengerByName();
            }
            break;
      
          default:
            break;
        }
      break;

      // Меню рейсов
      case 1:
        switch (flightsMenu.execute())
        {      
          case -1:
            break;
      
          case 0:
            newFlight();
            break;
      
          case 1:
            deleteFlight();
            break;
      
          case 2:
            showAllFlights();
            break;
      
          case 3:
            searchFlightByAirport();
            break;

          case 4:
            searchFlightByNumber();
            break;

          default:
            break;
      }
      break;

      // Меню билетов
      case 2:
      switch (ticketsMenu.execute())
      { 
        case -1:
          break;

        case 0:
          newTicket();
          break;

        case 1:
          returnTicket();
          break;

        case 2:
          showAllTickets();
          break;
       }
      break;

    // Демо
    case 3:
      demo();
      break;

    default:
      break;
    }
  }
}


// Demo
void demo(void)
{
  system("cls");
  utils::printHeader("Вывод таблицы пассажиров с тестовыми записями"); 

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
  cout << endl;

  utils::printHeader("Удаление записи, имеющей коллизии в хэш-таблице (Волкова Ольга Викторовна)");

  pair<string, string> passengerToRemove = 
    make_pair("passportNumber", "4000-000056");
  passengers->remove(passengerToRemove);

  cout << *passengersTable;
  system("pause");

  
  // Тест рейсов

  system("cls");

  utils::printHeader("Вывод таблицы рейсов с тестовыми записями");

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


  initializer_list<string> testFlight6InitList = {
    "000-006", "Россия", "Москва VKO",
    "Санкт-Петербург Пулково LED", "11 Июня, 20:05", "95", "95"
  };

  Flight testFlight6(testFlight6InitList);
  flights->insert(testFlight6);
  flightsTable->addRow(testFlight6.getVector());



  initializer_list<string> testFlight7InitList = {
    "000-007", "Победа", "Санкт-Петербург Пулково LED",
    "Берлин SXF", "11 Июня, 08:05", "165", "165"
  };

  Flight testFlight7(testFlight7InitList);
  flights->insert(testFlight7);
  flightsTable->addRow(testFlight7.getVector());

  flightsTable->removeAll();

  flights->addPostOrder();

  cout << *flightsTable << endl << "Дерево:" << endl;
  flights->printTree();

  system("pause");

  utils::printHeader("Удаление корня дерева (запись 000-004)");
  flights->removeRoot();

  cout << *flightsTable << endl << "Дерево:" << endl;
  flights->printTree();

  system("pause");

  flights->displaySearchByPattern(static_cast<string>("улков"));
  system("pause");

  flights->displaySearchByPattern(static_cast<string>("одед"));
  system("pause");

  flights->displaySearchByPattern(static_cast<string>("о LED"));
  system("pause");

  flights->displaySearchByPattern(static_cast<string>("Воркута"));

  system("pause");

  system("cls");

  Ticket ticket1(Passenger(testPassenger1InitializerList), testFlight2);
  Ticket ticket2(Passenger(testPassenger2InitializerList), testFlight1);
  Ticket ticket3(Passenger(testPassenger3InitializerList), testFlight2);
  Ticket ticket4(Passenger(testPassenger4InitializerList), testFlight3);

  tickets->pushBack(ticket1);
  tickets->pushBack(ticket2);
  tickets->pushBack(ticket3);
  tickets->pushBack(ticket4);

  utils::printHeader("СПИСОК БИЛЕТОВ");

  cout << *ticketsTable << endl;

  cout << endl << "Отсортированный список" << endl;
  tickets->insertionSort();
  cout << *ticketsTable << endl;
  system("pause");

}


void newPassenger(void)
{
  utils::printHeader("НОВЫЙ ПАССАЖИР");

  string queries[] = { 
    "Номер паспорта", "Дата выдачи", "ФИО", "Дата рождения" 
  };

  string s[4];
  for (int i = 0; i < 4; i++) {
    cin.ignore(cin.rdbuf()->in_avail());
    cout << setw(25) << left << queries[i] << ">> ";
    getline(cin, s[i]);
  }

  initializer_list<string> passengerInitList = { 
    s[0], s[1], s[2], s[3] 
  };

  try {
    Passenger passenger(passengerInitList);
    passengers->insert(HashEntry(passenger));
    passengersTable->addRow(passenger.getVector());
    showAllPassengers();
    system("pause");
  } 
  catch (...) {
    return;
  } // TODO
}


void deletePassenger(void)
{
  showAllPassengers();

  utils::printHeader("УДАЛЕНИЕ ЗАПИСИ О ПАССАЖИРЕ");
  cout << setw(25) << left << "Номер паспорта" << ">> ";
  string s;
  cin.ignore(cin.rdbuf()->in_avail());
  getline(cin, s);

  pair<string, string> p = make_pair("passportNumber", s);

  if (passengers->remove(p)) {
    cout << "Данные о пассажире успешно удалены" << endl;
  }
  else {
    cout << "Пассажир с введенным номером паспорта не найден" << endl;
  }

  system("pause");
}


void showAllPassengers(void)
{
  system("cls");

  utils::printHeader("СПИСОК ПАССАЖИРОВ");
  cout << *passengersTable << endl;
}

void searchPassengerByName(void)
{
  system("cls");

  utils::printHeader("ПОИСК ПАССАЖИРОВ ПО ИМЕНИ");
  cout << setw(25) << left << "Имя или часть имени" << ">> ";

  string s;
  cin.ignore(cin.rdbuf()->in_avail());
  getline(cin, s);

  passengers->displaySearchByName(s);
  system("pause");
}


void searchPassengerByPassport(void)
{
  system("cls");

  utils::printHeader("ПОИСК ПАССАЖИРА ПО НОМЕРУ ПАСПОРТУ");
  cout << setw(25) << left << "Номер паспорта" << ">> ";
  
  string s;
  cin.ignore(cin.rdbuf()->in_avail());
  getline(cin, s);

  passengers->displaySearchByPassport(s);
  system("pause");
}


void newFlight(void)
{
  string queries[] = { 
    "Номер рейса", "Авиакомпания", "Аэропорт отправления", "Аэропорт прибытия",
    "Дата отправления", "Время отправления", "Всего мест" 
  };

  string s[7];
  for (int i = 0; i < 7; i++) {
    cin.ignore(cin.rdbuf()->in_avail());
    cout << setw(25) << left << queries[i];
    getline(cin, s[i]);
  }

  initializer_list<string> flightInitList = { 
    s[0], s[1], s[2], s[3], s[4], s[5], s[6]
  };

  try {
    Flight flight(flightInitList);
    flights->insert(flight);
    totalFlights++;
    cout << "Рейс успешно добавлен" << endl << *flightsTable;
    system("pause");
  }
  catch (...) {
    return;
  } // TODO
}


void deleteFlight(void)
{
  system("cls");
  cout << *flightsTable << endl;

  utils::printHeader("УДАЛЕНИЕ АВИАРЕЙСА");
  cout << setw(25) << left << "Номер авиарейса" << ">> ";

  string s;
  cin.ignore(cin.rdbuf()->in_avail());
  getline(cin, s);

  if (flights->remove(s)) {
    totalFlights--;
    cout << "Авиарейс успешно удален" << endl;
  }
  else {
    cout << "Авиарейс не найден" << endl;
  }

  system("pause");
}


void searchFlightByAirport(void)
{
  system("cls");

  utils::printHeader("ПОИСК РЕЙСОВ ПО АЭРОПОРТУ ОТПРАВЛЕНИЯ");
  cout << "Паттерн" << endl << setw(25) << left << ">> ";

  string s;
  cin.ignore(cin.rdbuf()->in_avail());
  getline(cin, s);

  flights->displaySearchByPattern(s);

  system("pause");
}


void searchFlightByNumber(void)
{
  system("cls");

  utils::printHeader("ПОИСК РЕЙСОВ ПО НОМЕРУ АВИАРЕЙСА");
  cout << "Паттерн" << endl << setw(25) << left << ">> ";

  string s;
  cin.ignore(cin.rdbuf()->in_avail());
  getline(cin, s);

  flights->displaySearchByNumber(s);

  system("pause");
}


void showAllFlights(void)
{
  system("cls");
  
  utils::printHeader("СПИСОК АВИАРЕЙСОВ");
  cout << *flightsTable << endl;

  system("pause");
}


void newTicket(void)
{
  system("cls");

  utils::printHeader("ПРОДАЖА БИЛЕТА");
  cout << *passengersTable;
  cout  << setw(25) << left << "Номер паспорта пассажира" << ">> ";

  cin.ignore(cin.rdbuf()->in_avail());
  string passportNo;
  getline(cin, passportNo);

  if (!passengers->contains(
         make_pair(static_cast<string> ("passportNumber"),
                                         passportNo))) {
    cout << "Пассажир с введенным номером паспорта не найден" << endl;
  }
  else {
    cout << *flightsTable;
    cout << setw(25) << left << "Номер авиарейса" << ">> ";
    string flightNo;
    cin.ignore(cin.rdbuf()->in_avail());
    getline(cin, flightNo);
    if (!flights->contains(flightNo)) {
      cout << "Рейс с таким номером не найден" << endl;
    }
    else {
      Ticket ticket(
        passengers->find(make_pair(static_cast<string> ("passportNumber"),
                                   passportNo))->getValue(),
        *flights->searchByNumber(flightNo)
        );
      tickets->pushBack(ticket);
    }
  }   
  totalTickets++;
  system("pause");
}


void showAllTickets(void)
{
  system("cls");

  utils::printHeader("СПИСОК БИЛЕТОВ");
  cout << *ticketsTable << endl;
  system("pause");
}


void returnTicket(void)
{
  system("cls");
  utils::printHeader("ОФОРМИТЬ ВОЗВРАТ БИЛЕТА");
  showAllTickets();

  string s;
  cout << setw(25) << left << "Номер билета" << ">> ";
  cin.ignore(cin.rdbuf()->in_avail());
  getline(cin, s);

  if (tickets->returnTicket(s)) {
    totalTickets--;
    cout << "Билет отмечен как возвращенный" << endl;
  }
  else {
    cout << "Билет с таким номером не найден" << endl;
  }

  system("pause");
}
