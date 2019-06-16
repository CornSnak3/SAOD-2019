#include <exception>
#include <iomanip>
#include <iostream>
#include <string>

#include "DoublyLinkedList.h"
#include "Ticket.h"

struct listOutOfBoundsException : public std::exception
{
  const char * what() const throw () {
    return "Out of bounds";
  }
};

// Public DoublyLinkedList

DoublyLinkedList::DoublyLinkedList() : 
  size_(0), head_(nullptr), tail_(nullptr) { }


DoublyLinkedList::~DoublyLinkedList()
{
  this->emptyList();
}



void DoublyLinkedList::pushBack(Ticket& ticket)
{
  Node* newNode = createNode(ticket);

  if (head_ == nullptr) {
    head_ = newNode;
  }
  else {
    if (tail_ == nullptr) {
      tail_       = newNode;
      head_->next = tail_;
      tail_->prev = head_;
    }
    else {
      Node* prevTail = tail_;
      newNode->prev  = prevTail;
      prevTail->next = newNode;
      tail_ = newNode;
    }
  }

  size_++;
}


void DoublyLinkedList::remove(int index)
{
  Node* nodeTodelete = nullptr;

  try {
    nodeTodelete = at(index);
    removeNode(nodeTodelete);
  }
  catch (listOutOfBoundsException &e) {
    std::cout << e.what() << index << std::endl;
  }
}


void DoublyLinkedList::remove(Ticket& data)
{
  Node* currentNode = head_;

  while (currentNode != nullptr) {
    if (data == currentNode->data) {
      removeNode(currentNode);
      return;
    }

    currentNode = currentNode->next;
  }
}

// TODO
bool DoublyLinkedList::returnTicket(std::string passportNumber)
{
  for (int i = 0; i < this->size_; i++) {
    if (this->at(i)->data.getTicketNumber() == passportNumber) {
      return this->at(i)->data.flipStatus();
    }
  }
  return false;
}


void DoublyLinkedList::insertionSort(void)
{
  for (int i = 0; i < this->size_; i++) {
    Node* newHead = findMin();
    remove(newHead->data);

    head_->prev = newHead;
    newHead->prev = nullptr;
    newHead->next = head_;
    head_ = newHead;
  }
}


DoublyLinkedList::Node* DoublyLinkedList::findMin() const
{
  Node*  node = head_;
  Node*  retNode;
  Ticket min;

  while (node != nullptr) {
    if (node->data < min) {
      min     = node->data;
      retNode = node;
    }

    node = node->next;
  }
  return retNode;
}



int DoublyLinkedList::getSize(void)
{
  return this->size_;
}


std::string DoublyLinkedList::getNextTicketNumber(void)
{
  std::string number = std::to_string(size_ + 1);
  number.insert(number.begin(), 9 - number.length(), '0');
  return number;
}



//Private DoublyLinkedList

DoublyLinkedList::Node* DoublyLinkedList::at(int index) 
{
  if (index > size_)
    throw new listOutOfBoundsException();
  
  Node* currentNode = head_;
  for (int i = 0; i < index; i++) {
    currentNode = currentNode->next;
  }

  return currentNode;
}


 DoublyLinkedList::Node* DoublyLinkedList::createNode(Ticket& data)
{
  Node* newNode = new Node;
  newNode->data = data;
  newNode->next = nullptr;
  newNode->prev = nullptr;
  return newNode;
}
 

void DoublyLinkedList::emptyList(void)
{
  Node* currentNode = head_;

  while (currentNode != nullptr) {
    Node* next = currentNode->next;
    delete currentNode;
    currentNode = next;
  }
}


void DoublyLinkedList::removeNode(Node* nodeToDelete) 
{
  Node* prevNode = nodeToDelete->prev;
  Node* nextNode = nodeToDelete->next;

  if (prevNode == nullptr) {
    head_ = nullptr;
    head_ = nextNode;

    if (head_ != nullptr) {
      head_->prev = nullptr;
    }

  } else if (nextNode == nullptr) {
    tail_ = nullptr;
    tail_ = prevNode;

    if (this->tail_ != nullptr) {
      tail_->next = nullptr;
    }
  } else  {
    nextNode->prev = prevNode;
    prevNode->next = nextNode;
  }

  delete nodeToDelete;
  size_--;
}


