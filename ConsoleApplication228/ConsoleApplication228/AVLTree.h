#include<algorithm>
#include<iostream>
#include <vector>

#include "ConsoleTable.h"
#include "Flight.h"

class AVLTree {
private:

  struct treeNode {
    Flight data;
    treeNode *left;
    treeNode *right;
    int height;
  };

  ConsoleTable *linkedTable;

  treeNode *root;

  void makeEmpty(treeNode *t);

  treeNode *insert(Flight &, treeNode *);

  treeNode *singleRightRotate(treeNode * &);
  treeNode *singleLeftRotate(treeNode * &);
  treeNode *doubleRightRotate(treeNode * &);
  treeNode *doubleLeftRotate(treeNode * &);
  treeNode *findMin(treeNode *);
  treeNode *findMax(treeNode *);


    
  treeNode *remove(Flight &, treeNode *);

  int height(treeNode *);
  int getBalance(treeNode *);
  
  void postOrder(treeNode *, std::vector<Flight> *);
  void postOrder(treeNode *, std::string, std::vector<Flight> *);

  void searchByNumber(std::string, treeNode *, std::vector<Flight> *);
  std::vector<Flight> *searchByPattern(std::string);

public:
  AVLTree(ConsoleTable *);
  ~AVLTree();

  void addPostOrder(treeNode *);

  treeNode *removeRoot();

  void insert(Flight &);

  void removeAll() { makeEmpty(root); }

  void displaySearchByNumber(std::string);
  void displaySearchByPattern(std::string);
  void addPostOrder();

};
