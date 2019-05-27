#include <array>
#include <cstdlib>
#include <exception>
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
AVLTree *airFlights = new AVLTree();
DoublyLinkedList *tickets = new DoublyLinkedList();

//MENUS[Level[0]] = Заголовок

vector<vector<string>> menus = {
  { "Пассажиры", "Авиарейсы", "Билеты", "Выход"                                           },
  { "Зарегистрировать пассажира", "Удалить данные о пассажире", "Показать всех пассажиров",
    "Поиск пассажира по ФИО", "Поиск пассажира по № паспорта", "Назад"                    },
  { "Добавить авиарейс", "Поиск авиарейса по №", "Поиск авиарейса по аэропорту", 
    "Удалить авиарейс", "Показать все авиарейсы", "Очистить данные", "Назад"              },
  { "Продажа билета", "Возврат билета", "Назад"                                           }
};

void showMenu() {
  int currentPos = 0;
  for (int i = 0; i < menus[0].size(); i++) {
    system("CLS");
    if (i == currentPos)
      cout << "\t@";
    else
      cout << "\t ";
    cout << menus[0][i] << endl;
  }
//  getch();
}

void addPassenger();
void deletePassenger();
void showAllPassengers();
void searchPassengerByName();
void searchPassengerByPassport();


void addAirFlight(string, int *);
void addTicket(string);

int inputint() {
  int x; int i = 0;
  std::cin >> x;
  while (std::cin.fail() || std::cin.get() != '\n') {
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
  };
  std::cin >> x;
  return x;
}

int main(int argc, char *argv[]) {
  int passengerTotal = 0;
  int menu = 1;
  while (menu) {
    cout << "1 Passengers" << endl << "2 Flights" << "3 Tickets" << endl << "0 Exit" << endl << ">>";
    menu = inputint();
    if (menu == 0)
      break;
    else if (menu == 1) { //Passengers
        int submenu = 1;
      while (submenu) {
        system("cls");
        cout << "1 Add Passenger" << endl;
        if (passengerTotal > 0)
          cout << "2 Delete Passenger" << endl << "3 Show all Passengers" << endl <<
          "4 Search Passenger by Full Name" << endl << "5 Search Passenger by Passport" << endl;
        cout << "0 Back" << endl << ">>";
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
          searchPassengerByNumber();
        //getchar();
      }
    } else if (
      menu == 2) //books
    {
      int submenu = 1;
      while (submenu)
      {
        //system("cls");
        std::cout << "Now working with books. Please input:" << std::endl << "1
          to add a new book; " << std::endl;
          if (booktotal > 0)
            std::cout << "2 to delete a book;" << std::endl << "3 to output data
            for all books; " << std::endl
              << "4 to clear all data about books;" << std::endl << "5 to search
              book by chiper; " << std::endl
              << "6 to search book by title/author;" << std::endl;
        std::cout << "0 to go back to previous menu." << std::endl << ">>";
        submenu = inputint();
        if (submenu == 0)
          break;
        else if (submenu == 1)
          book_add(BookStorage, booktotal);
        else if (submenu == 2 && booktotal > 0)
          book_delete(BookStorage, booktotal);
        else if (submenu == 3 && booktotal > 0)
          tree_print(BookStorage, 0);
        else if (submenu == 4 && booktotal > 0)
          book_delete_all(BookStorage, booktotal);
        else if (submenu == 5 && booktotal > 0)
          book_search_chiper(BookStorage, AllData, ReaderHash);
        else if (submenu == 6 && booktotal > 0) //Under construction
          38
          book_search_other(BookStorage, booktotal);
        else
          std::cout << "Wouldn't you believe it, there is no such item on the
          menu!" << std::endl;
          //getchar();
      }
    }
    else if (
      menu == 3
      && booktotal >
      0
      && readertotal >
      0) //data
    {
      int submenu = 1;
      while (submenu)
      {
        //system("cls");
        std::cout << "Now working with issue data. Please input:" << std::endl
          << "1 to register the issuance of a copy of the book to the reader;" <<
          std::endl;
        if (datatotal > 0)
          std::cout << "2 to register the return of a copy of the book from the
          reader; " << std::endl;
          std::cout << "0 to go back to previous menu." << std::endl << ">>";
        submenu = inputint();
        if (submenu == 0)
          break;
        else if (submenu == 1)
          data_add(AllData, datatotal, ReaderHash, BookStorage);
        else if (submenu == 2 && datatotal > 0)
          data_delete(AllData, datatotal, ReaderHash, BookStorage);
        else if (submenu == 3 && datatotal > 0)
          list_output(AllData);
        else
          std::cout << "Believe it or not, there is no such item on the menu. "
          << std::endl;
        //getchar();
      }
    }
    else
      std::cout << "Regrettably, there is no such item on the menu. " << std::endl;
    //getchar();
}

void addPassenger() {
  string s[4];
  cout << "Full name: ";
  getline(cin, s[2]);
  cout << "Birthday date: ";
  getline(cin, s[3]);
  cout << "Passport number: "
  getline(cin, s[0]);
  cout << "Passport date of issue: ";
  getline(cin, s[1]);
  try {
    Passenger passenger(s);
    passengers.insert(HashEntry(passenger));
  } catch (exception &e) {
    cerr << e.what();
  }
  system("CLS");
  passengerTotal++;
  passengers.display();
}

void deletePassenger() {
  string s;
  do {
    cout << "Enter Passport Number: ";
    getline(cin, s);
    if (passengers.remove(s))
      break;
  } while (1 || s == "0");
}

void showAllPassengers() {
  system("CLS");
  passengers.display();
  cout << "Press ENTER to return";
  cin.get();
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
