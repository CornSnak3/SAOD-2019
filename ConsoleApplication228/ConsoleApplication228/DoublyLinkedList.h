#ifndef SAOD_DOUBLYLINKEDLIST_H
#define SAOD_DOUBLYLINKEDLIST_H

#include <iostream>
#include <string>

#include "ConsoleTable.h"
#include "Ticket.h"


class DoublyLinkedList {

public:

  DoublyLinkedList (ConsoleTable *);
  ~DoublyLinkedList();

  void    pushBack      (Ticket &);
  void    remove        (int);
  void    remove        (Ticket&);
  bool    returnTicket  (std::string);
  void    insertionSort (void);

  int         getSize             (void);
  std::string getNextTicketNumber (void);


private:

  struct Node {
    Ticket data;
    Node*  next;
    Node*  prev;
  };

  ConsoleTable* linkedTable_;

  int   size_;
  Node* head_;
  Node* tail_;


  Node* at           (int);
  Node* createNode   (Ticket&);
  Node* findMin      (int);
  void  emptyList    (void);
  void  removeNode   (Node*);
  void  updateTable  (void);
  void  swap         (Node*, Node*);

};

#endif // SAOD_DOUBLYLINKEDLIST_H