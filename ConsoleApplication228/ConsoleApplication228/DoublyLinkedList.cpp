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

DoublyLinkedList::DoublyLinkedList(ConsoleTable *linkedTable) : 
  size_(0), head_(nullptr), tail_(nullptr), linkedTable_(linkedTable) { }


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
  linkedTable_->addRow(ticket.getVector());
}


//void DoublyLinkedList::pushBack(Node* node)
//{
//  if (head_ == nullptr)
//    head_ == newNode;
//}



void DoublyLinkedList::remove(int index)
{
  Node* nodeTodelete = nullptr;

  try {
    nodeTodelete = at(index);
    removeNode(nodeTodelete);
    updateTable();
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
      updateTable();
      return;
    }

    currentNode = currentNode->next;
  }
}

// TODO
bool DoublyLinkedList::returnTicket(std::string passportNumber)
{
  for (int i = 0; i < size_; i++) {
    if (at(i)->data.getTicketNumber() == passportNumber) {
      at(i)->data.flipStatus();
      updateTable();
      return true;
    }
  }
  return false;
}


void DoublyLinkedList::insertionSort(void)
{
  std::vector<Node> vec;

  int size = size_;

  for (int i = 0; i < size; i++) {
    auto *temp = findMin(0);
    vec.push_back(*temp);
    remove(temp->data);
  }

  emptyList();
  updateTable();

  for (Node &n : vec) {
    pushBack(n.data);
  }
 
}


DoublyLinkedList::Node* DoublyLinkedList::findMin(int startPosition)
{
  Node*  node = at(startPosition);
  Node*  retNode;
  std::string params[] = { "", "", "999999999" };
  Ticket min(params);

  while (node != nullptr) {
    if (node->data < min) {
      min     = node->data;
      retNode = node;
    }

    node = node->next;
  }
  return retNode;
}

void DoublyLinkedList::swap(Node* n1, Node* n2) {

  std::cout << "Swapping " << n1->data.getTicketNumber() << " <-> " <<
    n2->data.getTicketNumber() << std::endl;

  if (n1->data == n2->data)
    return;

  Node* temp = new Node;

  temp->prev = n1->prev;
  temp->next = n1->next;

  n1->prev = n2->prev;
  n1->next = n2->next;

  n2->prev = temp->prev;
  n2->next = temp->next;

  if (n1->next != nullptr)
    n1->next->prev = n2;
  if (n1->prev != nullptr)
    n1->prev->next = n2;
  if (n2->next != nullptr)
    n2->next->prev = n1;
  if (n2->prev != nullptr)
    n2->prev->next = n1;

  delete temp;

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

  head_ = tail_ = nullptr;
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

void DoublyLinkedList::updateTable(void)
{
  linkedTable_->removeAll();
  Node* currentNode = head_;
  while (currentNode != nullptr) {
    linkedTable_->addRow(currentNode->data.getVector());
    currentNode = currentNode->next;
  }
}


