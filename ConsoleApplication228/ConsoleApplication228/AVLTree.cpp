#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "AVLTree.h"
#include "ConsoleTable.h"
#include "Flight.h"
#include "Utils.h"

// Public AVLTree

AVLTree::AVLTree(ConsoleTable *linkedTable) :
  root_(nullptr), linkedTable_(linkedTable) { }


AVLTree::~AVLTree(void) 
{
  makeEmpty(root_);
}



void AVLTree::addPostOrder(void) 
{
  addPostOrder(root_);
}


void AVLTree::addPostOrder(TreeNode* treeNode) 
{
  if (treeNode == nullptr) {
    return;
  }

  addPostOrder(treeNode->left);
  addPostOrder(treeNode->right);

  linkedTable_->addRow(treeNode->data.getVector());
}


bool AVLTree::remove(std::string& flightNumber)
{
  bool res = (remove(flightNumber, root_) == nullptr);
  linkedTable_->removeAll();
  addPostOrder(root_);
  return res;
}


AVLTree::TreeNode *AVLTree::removeRoot()
{
  TreeNode* returnNode = remove(root_->data.getField("flightNumber"), root_);

  linkedTable_->removeAll();

  addPostOrder(root_);
  return returnNode;
}


void AVLTree::insert(Flight &flight)
{
  root_ = insert(flight, root_);
  linkedTable_->removeAll();
  addPostOrder(root_);
}


void AVLTree::removeAll(void)
{
  makeEmpty(root_);
}


void AVLTree::printTree(void)
{
  printTree(root_, 0);
  std::cout << std::endl;
}


bool AVLTree::contains(std::string& number)
{
  std::vector<Flight>* foundFlights = new std::vector<Flight>();
  searchByNumber(number, root_, foundFlights);
  bool ret = foundFlights->empty();
  delete foundFlights;
  return ret;
}


Flight * AVLTree::searchByNumber(std::string& number)
{
  std::vector<Flight>* foundFlights = new std::vector<Flight>();
  searchByNumber(number, root_, foundFlights);
  Flight *ret = (foundFlights->empty()) ? nullptr : &(foundFlights->front());
  delete foundFlights;
  return ret;
}



void AVLTree::displaySearchByNumber(std::string& number)
{
  std::vector<Flight>* searchResults = new std::vector<Flight>();
  searchByNumber(number, root_, searchResults);
  
  if (searchResults->empty() || searchResults == nullptr) {
    utils::printHeader("���� � �������'" + number + "' �� ������");
  }
  else {
    system("cls");
    utils::printHeader("����� ����������");

    ConsoleTable *tempTable = new ConsoleTable{
      "����� �����", "������������", "�����������", "��������",
      "����� ������", "����� ����", "�������� ����" 
    };

    for (auto &entry : * searchResults) {
      auto rowVector = entry.getVector();
      tempTable->addRow(rowVector);
    }

    std::cout << *tempTable;
    delete tempTable;

    delete searchResults;
  }
}


void AVLTree::displaySearchByPattern(std::string& pattern)
{
  system("cls");
  std::cout << *linkedTable_;
  utils::printHeader("����� ������ �� ��������: '" + pattern + "'");

  std::vector<Flight> *searchResults = searchByPattern(pattern);

  ConsoleTable *tempTable = new ConsoleTable{ 
    "����� �����", "������������", "�����������", "��������",
    "����� ������", "����� ����", "�������� ����" 
  };

  for (auto &entry : * searchResults) {
    auto rowVector = entry.getVector();
    tempTable->addRow(rowVector);
  }

  std::cout << *tempTable;
  delete tempTable;
}



// Private AVLTree

void AVLTree::makeEmpty(TreeNode *startNode)
{
  if (startNode == nullptr) {
    return;
  }

  makeEmpty(startNode->left);
  makeEmpty(startNode->right);

  delete startNode;
}


AVLTree::TreeNode* AVLTree::insert(Flight& flight, TreeNode* treeNode)
{
  if (treeNode == nullptr) {
    treeNode         = new TreeNode;
    treeNode->data   = flight;
    treeNode->height = 0;
    treeNode->left   = treeNode->right = nullptr;
  } 
  else if (flight < treeNode->data) {
    treeNode->left = insert(flight, treeNode->left);

    if (height(treeNode->left) - height(treeNode->right) == 2) {
      if (flight < treeNode->left->data) {
        treeNode = singleRightRotate(treeNode);
      }
      else {
        treeNode = doubleRightRotate(treeNode);
      }
    }

  } 
  else if (flight > treeNode->data) {
    treeNode->right = insert(flight, treeNode->right);

    if (height(treeNode->right) - height(treeNode->left) == 2) {
      if (flight > treeNode->right->data) {
        treeNode = singleLeftRotate(treeNode);
      }
      else {
        treeNode = doubleLeftRotate(treeNode);
      }
    }

  } 

  treeNode->height = std::max(height(treeNode->left), height(treeNode->right)) + 1;

  return treeNode;
}


AVLTree::TreeNode* AVLTree::singleRightRotate(TreeNode* treeNode)
{
  TreeNode* u    = treeNode->left;
  treeNode->left = u->right;
  u->right       = treeNode;

  treeNode->height = std::max(height(treeNode->left), height(treeNode->right)) + 1;
  u->height        = std::max(height(u->left), treeNode->height) + 1;

  return u;
}


AVLTree::TreeNode* AVLTree::singleLeftRotate(TreeNode* treeNode)
{
  TreeNode* u     = treeNode->right;
  treeNode->right = u->left;
  u->left         = treeNode;

  treeNode->height = std::max(height(treeNode->left), height(treeNode->right)) + 1;
  u->height        = std::max(height(treeNode->right), treeNode->height) + 1;

  return u;
}


AVLTree::TreeNode* AVLTree::doubleRightRotate(TreeNode* treeNode) 
{
  treeNode->left = singleLeftRotate(treeNode->left);
  return singleRightRotate(treeNode);
}


AVLTree::TreeNode* AVLTree::doubleLeftRotate(TreeNode* treeNode)
{
  treeNode->right = singleRightRotate(treeNode->right);
  return singleLeftRotate(treeNode);
}

AVLTree::TreeNode* AVLTree::findMin(TreeNode* treeNode)
{
  if (treeNode == nullptr) {
    return nullptr;
  }
  else if (treeNode->left == nullptr) {
    return treeNode;
  }
  else {
    return findMin(treeNode->left);
  }
}


AVLTree::TreeNode* AVLTree::findMax(TreeNode* treeNode)
{
  if (treeNode == nullptr) {
    return nullptr;
  }
  else if (treeNode->right == nullptr) {
    return treeNode;
  }
  else {
    return findMax(treeNode->right);
  }
}


AVLTree::TreeNode* AVLTree::remove(std::string& flightNumber, TreeNode* treeNode)
{
  TreeNode* temp;

  if (treeNode == nullptr) {
    return nullptr;
  }
  else if (flightNumber < treeNode->data.getField("flightNumber")) {
    treeNode->left = remove(flightNumber, treeNode->left);
  }
  else if (flightNumber > treeNode->data.getField("flightNumber")) {
    treeNode->right = remove(flightNumber, treeNode->right);
  }
  else if (treeNode->left && treeNode->right) {

    temp            = findMin(treeNode->right);
    treeNode->data  = temp->data;
    treeNode->right = remove(treeNode->data.getField("flightNumber"),
                             treeNode->right);
  } 
  else {
    temp = treeNode;
    if (treeNode->left == nullptr) {
      treeNode = treeNode->right;
    }
    else if (treeNode->right == nullptr) {
      treeNode = treeNode->left;
    }

    delete temp;
  }

  if (treeNode == nullptr) {
    return treeNode;
  }

  treeNode->height = std::max(height(treeNode->left), height(treeNode->right)) + 1;

  if (height(treeNode->left) - height(treeNode->right) == 2) {
    if (height(treeNode->left->left) - height(treeNode->left->right) == 1) {
      return singleLeftRotate(treeNode);
    }
    else {
      return doubleLeftRotate(treeNode);
    }
  } else if (height(treeNode->right) - height(treeNode->left) == 2) {
    if (height(treeNode->right->right) - height(treeNode->right->left) == 1) {
      return singleRightRotate(treeNode);
    }
    else {
      return doubleRightRotate(treeNode);
    }
  }

  return treeNode;
}


int AVLTree::height(TreeNode* node)
{
  return (node == nullptr ? -1 : node->height);
}


int AVLTree::getBalance(TreeNode* treeNode)
{
  if (treeNode == nullptr)
    return 0;
  else
    return height(treeNode->left) - height(treeNode->right);
}



void AVLTree::postOrder(TreeNode* startNode, std::vector<Flight>* flightVector)
{
  if (startNode == nullptr) {
    return;
  }

  postOrder(startNode->left, flightVector);
  postOrder(startNode->right, flightVector);
  flightVector->push_back(startNode->data);
}


void AVLTree::postOrder(TreeNode *t, std::string pattern, std::vector<Flight> *flightVector) {
  if (t == nullptr)
    return;
  postOrder(t->left, pattern, flightVector);
  postOrder(t->right, pattern, flightVector);

  if (t->data.searchBoyerMoore(pattern)) {
    flightVector->push_back(t->data);
  }
}



void AVLTree::printTree(TreeNode* root, int numberOfSpaces)
{
  if (root == nullptr) {
    return;
  }

  numberOfSpaces += 12;

  printTree(root->right, numberOfSpaces);

  std::cout << std::endl;

  for (int i = 12; i < numberOfSpaces; i++) {
    std::cout << " ";
  }

  std::cout << "|" << root->data.getField("flightNumber") << " <" << std::endl;

  printTree(root->left, numberOfSpaces);

}



std::vector<Flight>* AVLTree::searchByPattern(std::string& pattern)
{
  std::vector<Flight>* selection = new std::vector<Flight>();
  postOrder(root_, pattern, selection);
  return selection;
}


void AVLTree::searchByNumber
(std::string& number, TreeNode* treeNode, std::vector<Flight>* flightVector)
{
  if (treeNode == nullptr) {
    return;
  }

  if (number > treeNode->data.getField("flightNumber")) {
    return searchByNumber(number, treeNode->right, flightVector);
  }
  else if (number < treeNode->data.getField("flightNumber")) {
    searchByNumber(number, treeNode->left, flightVector);
  }
  else {
    flightVector->push_back(treeNode->data);
  }
}




