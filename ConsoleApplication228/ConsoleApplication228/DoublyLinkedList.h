#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <iostream>

#include "Ticket.h"

class DoublyLinkedList {
private:
  int size;

  typedef struct Node {
    Ticket data;
    Node* next;
    Node* prev;
  } *nodePtr;

  nodePtr head;
  nodePtr tail;

  nodePtr createNode(Ticket);
  nodePtr at(int);
  void emptyList();
  void removeNode(nodePtr);
  nodePtr findMin() const;

public:  
  DoublyLinkedList();
  ~DoublyLinkedList();
  void pushBack(const Ticket &);
  void remove(int);
  void remove(Ticket);
  void insertionSort();
  void display() const;
};

#endif // DOUBLYLINKEDLIST_H