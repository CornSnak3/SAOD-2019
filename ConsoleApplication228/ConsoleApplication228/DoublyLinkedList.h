#ifndef SAOD_DOUBLYLINKEDLIST_H
#define SAOD_DOUBLYLINKEDLIST_H

#include <iostream>
#include <string>

#include "Ticket.h"


class DoublyLinkedList {

public:

  DoublyLinkedList ();
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


  int   size_;
  Node* head_;
  Node* tail_;


  Node* at         (int);
  Node* createNode (Ticket&);
  Node* findMin    (void) const;
  void  emptyList  (void);
  void  removeNode (Node*);

};

#endif // SAOD_DOUBLYLINKEDLIST_H