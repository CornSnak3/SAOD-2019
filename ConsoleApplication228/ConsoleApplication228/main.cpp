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

// ��������
int totalPassengers = 0;
int totalFlights    = 0;
int totalTickets    = 0;

// ��������� ����������
ConsoleTable *passengersTable = new ConsoleTable {
  "����� ��������", "���� ������", "���", "���� ��������"
};

HashTable *passengers = new HashTable(32, passengersTable, 0.75,
                                      static_cast<string> ("passportNumber"));

// ��������� ����������
ConsoleTable *flightsTable = new ConsoleTable {
  "����� �����", "������������", "�����������", "��������", "����� ������",
  "����� ����", "�������� ����"
};

AVLTree *flights = new AVLTree(flightsTable);


// ��������� �������
ConsoleTable *ticketsTable = new ConsoleTable{
  "����� ������", "����� �������� ���������", "����� �����", "������"
};

DoublyLinkedList* tickets = new DoublyLinkedList(ticketsTable);


// ������� ������ � �����������
void newPassenger              (void);
void deletePassenger           (void);
void showAllPassengers         (void);
void searchPassengerByName     (void);
void searchPassengerByPassport (void);


// ������� ������ � �������
void newFlight             (void);
void deleteFlight          (void);
void deleteAllFlights      (void);
void searchFlightByAirport (void);
void searchFlightByNumber  (void);
void showAllFlights        (void);


// ������� ������ � ��������
void newTicket             (void);
void returnTicket          (void);
void deleteTicketsOnFlight (void);
void showAllTickets        (void);


// ����
void demo(void);


// �������� ����

void executeMenu(void);

initializer_list<string> mainMenuInitializerList       = {
  "������� �����������", "��������� ", "��������� ", "������    ", "����      " 
};

initializer_list<string> passengersMenuInitializerList = {
  "���������", "�������� ���������", "������� ���������", "������ ����������", "����� �� �������� ", "����� �� �����   " 
};

initializer_list<string> flightsMenuInitializerList    = { 
  "���������", "�������� ��������    ", "������� ��������     ",
  "������ ����������    ", "����� �� ���������   ", "����� �� ������ �����"
};

initializer_list<string> ticketsMenuInitialierList     = {
  "������", "������� ������", "������� ������", "������ �������"
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

      // ���� ����������
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

      // ���� ������
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

      // ���� �������
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

    // ����
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
  utils::printHeader("����� ������� ���������� � ��������� ��������"); 

  // ������������� ����������

  vector<initializer_list<string>> testPassengersInitializers;


  initializer_list<string> testPassenger1InitializerList = {
    "4009-846396", "20.09.2009", "������ ������ ����������", "31.08.1995" 
  };
  testPassengersInitializers.push_back(testPassenger1InitializerList);


  initializer_list<string> testPassenger2InitializerList = { 
    "4000-000023", "12.11.2002", "������ ������� �����������", "17.09.1967"
  };
  testPassengersInitializers.push_back(testPassenger2InitializerList);


  initializer_list<string> testPassenger3InitializerList = { 
    "4000-000056", "03.02.2000", "������� ����� ����������", "11.03.1967"
  };
  testPassengersInitializers.push_back(testPassenger3InitializerList);


  initializer_list<string> testPassenger4InitializerList = {
    "4000-000131", "08.05.2012", "�������� ��������� ��������", "07.05.1998"
  };
  testPassengersInitializers.push_back(testPassenger4InitializerList);


  initializer_list<string> testPassenger5InitializerList = {
    "3810-556131", "25.04.1992", "������  ������� ����", "20.02.1967"
  };
  testPassengersInitializers.push_back(testPassenger5InitializerList);


  initializer_list<string> testPassenger6InitializerList = {
    "2536-887544", "01.12.1979", "������ ����� ���", "15.06.1956"
  };
  testPassengersInitializers.push_back(testPassenger6InitializerList);


  initializer_list<string> testPassenger7InitializerList = {
    "3999-278045", "22.08.1999", "���� ����� ������", "22.08.1967"
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

  utils::printHeader("�������� ������, ������� �������� � ���-������� (������� ����� ����������)");

  pair<string, string> passengerToRemove = 
    make_pair("passportNumber", "4000-000056");
  passengers->remove(passengerToRemove);

  cout << *passengersTable;
  system("pause");

  
  // ���� ������

  system("cls");

  utils::printHeader("����� ������� ������ � ��������� ��������");

  initializer_list<string> testFlight2InitList = {
    "000-004", "S7 Airlines", "������ ���������� DME",
    "���� ����� AER", "11 ����, 20:10", "144", "144" 
  };

  Flight testFlight2(testFlight2InitList);
  flights->insert(testFlight2);
  flightsTable->addRow(testFlight2.getVector());


  initializer_list<string> testFlight3InitList ={ 
    "000-001", "��������", "�����-��������� ������� LED",
    "����� �����-2 MSQ", "11 ����, 20:05", "120", "120"
  };

  Flight testFlight3(testFlight3InitList);
  flights->insert(testFlight3);
  flightsTable->addRow(testFlight3.getVector());


  initializer_list<string> testFlight4InitList =
  { "000-002", "Tokio Air", "�����-��������� ������� LED",
    "����� ������ HND", "11 ����, 18:05", "174", "174"
  };

  Flight testFlight4(testFlight4InitList);
  flights->insert(testFlight4);
  flightsTable->addRow(testFlight4.getVector());

  initializer_list<string> testFlight5InitList = {
    "000-003", "��������", "�����-��������� ������� LED",
    "����� ������ HAN", "12 ����, 17:30", "100", "100"
  };

  Flight testFlight5(testFlight5InitList);
  flights->insert(testFlight5);
  flightsTable->addRow(testFlight5.getVector());

  initializer_list<string> testFlight1InitList = { 
    "000-005", "��������", "������ ����������� SVO",
    "�����-��������� ������� LED", "11 ����, 03:45", "180", "180"
  };


  Flight testFlight1(testFlight1InitList);
  flights->insert(testFlight1);
  flightsTable->addRow(testFlight1.getVector());


  initializer_list<string> testFlight6InitList = {
    "000-006", "������", "������ VKO",
    "�����-��������� ������� LED", "11 ����, 20:05", "95", "95"
  };

  Flight testFlight6(testFlight6InitList);
  flights->insert(testFlight6);
  flightsTable->addRow(testFlight6.getVector());



  initializer_list<string> testFlight7InitList = {
    "000-007", "������", "�����-��������� ������� LED",
    "������ SXF", "11 ����, 08:05", "165", "165"
  };

  Flight testFlight7(testFlight7InitList);
  flights->insert(testFlight7);
  flightsTable->addRow(testFlight7.getVector());

  flightsTable->removeAll();

  flights->addPostOrder();

  cout << *flightsTable << endl << "������:" << endl;
  flights->printTree();

  system("pause");

  utils::printHeader("�������� ����� ������ (������ 000-004)");
  flights->removeRoot();

  cout << *flightsTable << endl << "������:" << endl;
  flights->printTree();

  system("pause");

  flights->displaySearchByPattern(static_cast<string>("�����"));
  system("pause");

  flights->displaySearchByPattern(static_cast<string>("����"));
  system("pause");

  flights->displaySearchByPattern(static_cast<string>("� LED"));
  system("pause");

  flights->displaySearchByPattern(static_cast<string>("�������"));

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

  utils::printHeader("������ �������");

  cout << *ticketsTable << endl;

  cout << endl << "��������������� ������" << endl;
  tickets->insertionSort();
  cout << *ticketsTable << endl;
  system("pause");

}


void newPassenger(void)
{
  utils::printHeader("����� ��������");

  string queries[] = { 
    "����� ��������", "���� ������", "���", "���� ��������" 
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

  utils::printHeader("�������� ������ � ���������");
  cout << setw(25) << left << "����� ��������" << ">> ";
  string s;
  cin.ignore(cin.rdbuf()->in_avail());
  getline(cin, s);

  pair<string, string> p = make_pair("passportNumber", s);

  if (passengers->remove(p)) {
    cout << "������ � ��������� ������� �������" << endl;
  }
  else {
    cout << "�������� � ��������� ������� �������� �� ������" << endl;
  }

  system("pause");
}


void showAllPassengers(void)
{
  system("cls");

  utils::printHeader("������ ����������");
  cout << *passengersTable << endl;
}

void searchPassengerByName(void)
{
  system("cls");

  utils::printHeader("����� ���������� �� �����");
  cout << setw(25) << left << "��� ��� ����� �����" << ">> ";

  string s;
  cin.ignore(cin.rdbuf()->in_avail());
  getline(cin, s);

  passengers->displaySearchByName(s);
  system("pause");
}


void searchPassengerByPassport(void)
{
  system("cls");

  utils::printHeader("����� ��������� �� ������ ��������");
  cout << setw(25) << left << "����� ��������" << ">> ";
  
  string s;
  cin.ignore(cin.rdbuf()->in_avail());
  getline(cin, s);

  passengers->displaySearchByPassport(s);
  system("pause");
}


void newFlight(void)
{
  string queries[] = { 
    "����� �����", "������������", "�������� �����������", "�������� ��������",
    "���� �����������", "����� �����������", "����� ����" 
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
    cout << "���� ������� ��������" << endl << *flightsTable;
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

  utils::printHeader("�������� ���������");
  cout << setw(25) << left << "����� ���������" << ">> ";

  string s;
  cin.ignore(cin.rdbuf()->in_avail());
  getline(cin, s);

  if (flights->remove(s)) {
    totalFlights--;
    cout << "�������� ������� ������" << endl;
  }
  else {
    cout << "�������� �� ������" << endl;
  }

  system("pause");
}


void searchFlightByAirport(void)
{
  system("cls");

  utils::printHeader("����� ������ �� ��������� �����������");
  cout << "�������" << endl << setw(25) << left << ">> ";

  string s;
  cin.ignore(cin.rdbuf()->in_avail());
  getline(cin, s);

  flights->displaySearchByPattern(s);

  system("pause");
}


void searchFlightByNumber(void)
{
  system("cls");

  utils::printHeader("����� ������ �� ������ ���������");
  cout << "�������" << endl << setw(25) << left << ">> ";

  string s;
  cin.ignore(cin.rdbuf()->in_avail());
  getline(cin, s);

  flights->displaySearchByNumber(s);

  system("pause");
}


void showAllFlights(void)
{
  system("cls");
  
  utils::printHeader("������ ����������");
  cout << *flightsTable << endl;

  system("pause");
}


void newTicket(void)
{
  system("cls");

  utils::printHeader("������� ������");
  cout << *passengersTable;
  cout  << setw(25) << left << "����� �������� ���������" << ">> ";

  cin.ignore(cin.rdbuf()->in_avail());
  string passportNo;
  getline(cin, passportNo);

  if (!passengers->contains(
         make_pair(static_cast<string> ("passportNumber"),
                                         passportNo))) {
    cout << "�������� � ��������� ������� �������� �� ������" << endl;
  }
  else {
    cout << *flightsTable;
    cout << setw(25) << left << "����� ���������" << ">> ";
    string flightNo;
    cin.ignore(cin.rdbuf()->in_avail());
    getline(cin, flightNo);
    if (!flights->contains(flightNo)) {
      cout << "���� � ����� ������� �� ������" << endl;
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

  utils::printHeader("������ �������");
  cout << *ticketsTable << endl;
  system("pause");
}


void returnTicket(void)
{
  system("cls");
  utils::printHeader("�������� ������� ������");
  showAllTickets();

  string s;
  cout << setw(25) << left << "����� ������" << ">> ";
  cin.ignore(cin.rdbuf()->in_avail());
  getline(cin, s);

  if (tickets->returnTicket(s)) {
    totalTickets--;
    cout << "����� ������� ��� ������������" << endl;
  }
  else {
    cout << "����� � ����� ������� �� ������" << endl;
  }

  system("pause");
}
