#include <iomanip>
#include <iostream>

#include "DoublyLinkedList.h"
#include "Ticket.h"

using namespace std;

struct listOutOfBoundsException : public exception {
  const char * what() const throw () {
    return "Out of bounds";
  }
};

DoublyLinkedList::nodePtr DoublyLinkedList::findMin() const {
  nodePtr node = this->head;
  nodePtr retNode;
  Ticket min;
  while (node != nullptr) {
    if (node->data < min) {
      min = node->data;
      retNode = node;
    }
    node = node->next;
  }
  return retNode;
}

void DoublyLinkedList::insertionSort() {
  for (int i = 0; i < this->size; i++) {
    nodePtr newHead = findMin();
    remove(newHead->data);
    this->head->prev = newHead;
    newHead->prev = nullptr;
    newHead->next = this->head;
    this->head = newHead;
  }
}


 DoublyLinkedList::nodePtr DoublyLinkedList::createNode(Ticket data) {
  nodePtr newNode = new Node;
  newNode->data = data;
  newNode->next = nullptr;
  newNode->prev = nullptr;
  return newNode;
}

DoublyLinkedList::nodePtr DoublyLinkedList::at(int index) {
  if (this->size <= index)
    throw listOutOfBoundsException();

  int counter = 0;
  nodePtr node = this->head;

  while (counter != index && node != nullptr) {
    node = node->next;
    ++counter;
  }

  return node;
}

void DoublyLinkedList::emptyList() {
  nodePtr currentNode = this->head;
  while (currentNode != nullptr) {
    nodePtr next = currentNode->next;
    delete currentNode;
    currentNode = next;
  }
}

void DoublyLinkedList::removeNode(nodePtr nodeToDelete) {
  nodePtr prevNode = nodeToDelete->prev;
  nodePtr nextNode = nodeToDelete->next;

  if (prevNode == nullptr) {
    this->head = nullptr;
    this->head = nextNode;
    if (this->head != nullptr)
      this->head->prev = nullptr;

  } else if (nextNode == nullptr) {
    this->tail = nullptr;
    this->tail = prevNode;
    if (this->tail != nullptr)
      this->tail->next = nullptr;
  } else  {
    nextNode->prev = prevNode;
    prevNode->next = nextNode;
  }
  delete nodeToDelete;
  --this->size;
}

DoublyLinkedList::DoublyLinkedList() : size(0) {
  this->head = nullptr;
  this->tail = nullptr;
}

DoublyLinkedList::~DoublyLinkedList() {
  this->emptyList();
}

void DoublyLinkedList::pushBack(const Ticket &data) {
  nodePtr newNode = createNode(data);
  if (this->head == nullptr) {
    this->head = newNode;
  } else {
    if (this->tail == nullptr) {
      this->tail = newNode;
      this->head->next = this->tail;
      this->tail->prev = this->head;
    } else {
      nodePtr prevTail = this->tail;
      newNode->prev = prevTail;
      prevTail->next = newNode;
      this->tail = newNode;
    }
  }
  ++this->size;
}

void DoublyLinkedList::remove(int index) {
  nodePtr nodeTodelete = nullptr;
  try {
    nodeTodelete = at(index);
    removeNode(nodeTodelete);
  } catch (listOutOfBoundsException &e) {
    cout << e.what() << index << endl;
  }
}

void DoublyLinkedList::remove(Ticket data) {
  nodePtr currentNode = this->head;
  while (currentNode != nullptr) {
    if (data == currentNode->data)
      removeNode(currentNode);

    currentNode = currentNode->next;
  }
}

void DoublyLinkedList::display() const {
  cout << setw(15) << left << "TICKET #" << setw(15) 
    << "FLIGHT" << setw(15) << "PASSPORT" << endl;
  nodePtr currentNode = this->head;
  while (currentNode != nullptr) {
    cout << currentNode->data;
    currentNode = currentNode->next;
  }
}

string DoublyLinkedList::getNextTicketNumber() {
  string out = "000000000";
  int number = this->size + 1;
  for (int i = out.size() - 1; number > 0; i--) {
    out[i] = number % 10;
    number /= 10;
  }
  return out;
}