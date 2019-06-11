#include <algorithm>

#include "AVLTree.h"
#include "ConsoleTable.h"
#include "Utils.h"

// Private

void AVLTree::makeEmpty(treeNode *startNode){
  if (startNode == nullptr)
    return;
  makeEmpty(startNode->left);
  makeEmpty(startNode->right);
  delete startNode;
}

AVLTree::treeNode *AVLTree::insert(Flight &flight, treeNode *node) {
  if (node == nullptr) {
    node = new treeNode;
    node->data = flight;
    node->height = 0;
    node->left = node->right = nullptr;
  } else if (flight < node->data) {
    node->left = insert(flight, node->left);
    if (height(node->left) - height(node->right) == 2) {
      if (flight < node->left->data)
        node = singleRightRotate(node);
      else
        node = doubleRightRotate(node);
    }
  } else if (flight > node->data) {
    node->right = insert(flight, node->right);
    if (height(node->right) - height(node->left) == 2) {
      if (flight > node->right->data)
        node = singleLeftRotate(node);
      else
        node = doubleLeftRotate(node);
    }
  } 
  node->height = std::max(height(node->left), height(node->right)) + 1;
  addPostOrder(root);
  return node;
}

AVLTree::treeNode *AVLTree::singleRightRotate(treeNode * &node) {
  treeNode *u = node->left;
  node->left = u->right;
  u->right = node;
  node->height = std::max(height(node->left), height(node->right)) + 1;
  u->height = std::max(height(u->left), node->height) + 1;
  return u;
}

AVLTree::treeNode *AVLTree::singleLeftRotate(treeNode * &node) {
  treeNode *u = node->right;
  node->right = u->left;
  u->left = node;
  node->height = std::max(height(node->left), height(node->right)) + 1;
  u->height = std::max(height(node->right), node->height) + 1;
  return u;
}

AVLTree::treeNode *AVLTree::doubleRightRotate(treeNode * &node) {
  node->left = singleLeftRotate(node->left);
  return singleRightRotate(node);
}

AVLTree::treeNode *AVLTree::doubleLeftRotate(treeNode * &node) {
  node->right = singleRightRotate(node->right);
  return singleLeftRotate(node);
}

AVLTree::treeNode *AVLTree::findMin(treeNode *node) {
  if (node == nullptr)
    return nullptr;
  else if (node->left == nullptr)
    return node;
  else
    return findMin(node->left);
}

AVLTree::treeNode *AVLTree::findMax(treeNode *node) {
  if (node == nullptr)
    return nullptr;
  else if (node->right == nullptr)
    return node;
  else
    return findMax(node->right);
}

void AVLTree::addPostOrder() {
  addPostOrder(root);
}

void AVLTree::addPostOrder(treeNode *t) {
  if (t == nullptr)
    return;
  addPostOrder(t->left);
  addPostOrder(t->right);
  linkedTable->addRow(t->data.getVector());
}

AVLTree::treeNode *AVLTree::removeRoot() {  
  treeNode *returnNode = remove(root->data, root);
  linkedTable->removeAll();
  addPostOrder(root);
  return returnNode;
}

AVLTree::treeNode *AVLTree::remove(Flight &flight, treeNode *node) {
  treeNode *temp;
  if (node == nullptr)
    return nullptr;
  else if (flight < node->data)
    node->left = remove(flight, node->left);
  else if (flight > node->data)
    node->right = remove(flight, node->right);
  else if (node->left && node->right) {
    temp = findMin(node->right);
    node->data = temp->data;
    node->right = remove(node->data, node->right);
  } else {
    temp = node;
    if (node->left == nullptr)
      node = node->right;
    else if (node->right == nullptr)
      node = node->left;
    delete temp;
  }

  if (node == nullptr)
    return node;

  node->height = std::max(height(node->left), height(node->right)) + 1;

  if (height(node->left) - height(node->right) == 2) {
    if (height(node->left->left) - height(node->left->right) == 1)
      return singleLeftRotate(node);
    else
      return doubleLeftRotate(node);
  } else if (height(node->right) - height(node->left) == 2) {
    if (height(node->right->right) - height(node->right->left) == 1)
      return singleRightRotate(node);
    else
      return doubleRightRotate(node);
  }
  return node;
}

int AVLTree::height(treeNode *node) {
  return (node == nullptr ? -1 : node->height);
}

int AVLTree::getBalance(treeNode *t) {
  if (t == nullptr)
    return 0;
  else
    return height(t->left) - height(t->right);
}

void AVLTree::postOrder(treeNode *startNode, std::vector<Flight> *flightVector) {
  if (startNode == nullptr)
    return;
  postOrder(startNode->left, flightVector);
  postOrder(startNode->right, flightVector);
  flightVector->push_back(startNode->data);
}

void AVLTree::postOrder(treeNode *t, std::string pattern, std::vector<Flight> *flightVector) {
  if (t == nullptr)
    return;
  postOrder(t->left, pattern, flightVector);
  postOrder(t->right, pattern, flightVector);
  if (t->data.searchBoyerMoore(pattern))
    flightVector->push_back(t->data);
}

// Public

AVLTree::AVLTree(ConsoleTable *linkedTable) : root(nullptr), linkedTable(linkedTable) {}

AVLTree::~AVLTree() {
  makeEmpty(root);
}

void AVLTree::insert(Flight &flight) {
  root = insert(flight, root);
}

std::vector<Flight> *AVLTree::searchByPattern(std::string pattern) {
  std::vector<Flight> *selection = new std::vector<Flight>();
  postOrder(root, pattern, selection);
  return selection;
}

void AVLTree::searchByNumber(std::string number, treeNode *node, std::vector<Flight> *flightVector) {
  if (node == nullptr)
    return;

  if (number > node->data.getField("flightNumber"))
    return searchByNumber(number, node->right, flightVector);
  else if (number < node->data.getField("flightNumber"))
    searchByNumber(number, node->left, flightVector);
  else 
    flightVector->push_back(node->data);
}

void AVLTree::displaySearchByNumber(std::string number) {
  std::vector<Flight> *searchResults;
  searchByNumber(number, root, searchResults);
  if (searchResults->empty() || searchResults == nullptr) {
    Utils::printHeader("РЕЙС С НОМЕРОМ '" + number + "' НЕ НАЙДЕН");
  } else {
    system("cls");
    Utils::printHeader("ПОИСК АВИАРЕЙСОВ");

    ConsoleTable *tempTable = new ConsoleTable{ 
      "Номер рейса", "Авиакомпания", "Отправление", "Прибытие",
      "Время вылета", "Всего мест", "Свободно мест" };

    for (auto entry : *searchResults) {
      auto rowVector = entry.getVector();
      tempTable->addRow(rowVector);
    }
    std::cout << *tempTable;
    delete tempTable;
  }

}

void AVLTree::displaySearchByPattern(std::string pattern) {
  Utils::printHeader("ПОИСК ПО ПАТТЕРНУ '" + pattern + "'");
  std::vector<Flight> *searchResults = searchByPattern(pattern);
  ConsoleTable *tempTable =
    new ConsoleTable{ "Номер рейса", "Авиакомпания", "Отправление", "Прибытие",
                      "Время вылета", "Всего мест", "Свободно мест" };
  for (auto entry : *searchResults) {
    auto rowVector = entry.getVector();
    tempTable->addRow(rowVector);
  }
  std::cout << *tempTable;
  delete tempTable;
}
