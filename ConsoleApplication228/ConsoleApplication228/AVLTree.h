#include<algorithm>
#include<iostream>
#include <vector>

#include "Flight.h"

using namespace std;

class AVLTree {
  struct treeNode {
    Flight data;
    treeNode *left;
    treeNode *right;
    int height;
  };

  treeNode *root;

  void makeEmpty(treeNode *t) {
    if (t == nullptr)
      return;
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
  }

  treeNode *insert(const Flight &x, treeNode *t) {
    if (t == nullptr) {
      t = new treeNode;
      t->data = x;
      t->height = 0;
      t->left = t->right = nullptr;
    } else if (x < t->data) {
      t->left = insert(x, t->left);
      if (height(t->left) - height(t->right) == 2) {
        if (x < t->left->data)
          t = singleRightRotate(t);
        else
          t = doubleRightRotate(t);
      }
    } else if (x > t->data) {
      t->right = insert(x, t->right);
      if (height(t->right) - height(t->left) == 2) {
        if (x > t->right->data)
          t = singleLeftRotate(t);
        else
          t = doubleLeftRotate(t);
      }
    }

    t->height = max(height(t->left), height(t->right)) + 1;
    return t;
  }

  treeNode *singleRightRotate(treeNode * &t) {
    treeNode *u = t->left;
    t->left = u->right;
    u->right = t;
    t->height = max(height(t->left), height(t->right)) + 1;
    u->height = max(height(u->left), t->height) + 1;
    return u;
  }

  treeNode *singleLeftRotate(treeNode * &t) {
    treeNode *u = t->right;
    t->right = u->left;
    u->left = t;
    t->height = max(height(t->left), height(t->right)) + 1;
    u->height = max(height(t->right), t->height) + 1;
    return u;
  }

  treeNode *doubleLeftRotate(treeNode * &t)
  {
    t->right = singleRightRotate(t->right);
    return singleLeftRotate(t);
  }

  treeNode *doubleRightRotate(treeNode * &t)
  {
    t->left = singleLeftRotate(t->left);
    return singleRightRotate(t);
  }

  treeNode *findMin(treeNode *t) {
    if (t == nullptr)
      return nullptr;
    else if (t->left == nullptr)
      return t;
    else
      return findMin(t->left);
  }

  treeNode *findMax(treeNode *t) {
    if (t == nullptr)
      return nullptr;
    else if (t->right == nullptr)
      return t;
    else
      return findMax(t->right);
  }

  treeNode *remove(const Flight &x, treeNode *t) {
    treeNode *temp;
    if (t == nullptr)
      return nullptr;
    else if (x < t->data)
      t->left = remove(x, t->left);
    else if (x > t->data)
      t->right = remove(x, t->right);
    else if (t->left && t->right) {
      temp = findMin(t->right);
      t->data = temp->data;
      t->right = remove(t->data, t->right);
    } else {
      temp = t;
      if (t->left == nullptr)
        t = t->right;
      else if (t->right == nullptr)
        t = t->left;
      delete temp;
    }

    if (t == nullptr)
      return t;

    t->height = max(height(t->left), height(t->right)) + 1;

    if (height(t->left) - height(t->right) == 2) {
      if (height(t->left->left) - height(t->left->right) == 1)
        return singleLeftRotate(t);
      else
        return doubleLeftRotate(t);
    } else if (height(t->right) - height(t->left) == 2) {
      if (height(t->right->right) - height(t->right->left) == 1)
        return singleRightRotate(t);
      else
        return doubleRightRotate(t);
    }
    return t;
  }

  int height(treeNode *t) {
    return (t == nullptr ? -1 : t->height);
  }

  int getBalance(treeNode *t) {
    if (t == nullptr)
      return 0;
    else
      return height(t->left) - height(t->right);
  }

  void postOrder(treeNode *t, string pattern, vector<Flight> *v) {
    if (t == nullptr)
      return;
    postOrder(t->left, pattern, v);
    postOrder(t->right, pattern, v);
    if (t->data.searchBoyerMoore(pattern))
      v->push_back(t->data);
  }

  void postOrder(treeNode *t) {
    if (t == nullptr)
      return;
    postOrder(t->left);
    postOrder(t->right);
    cout << t->data;
  }

public:
  AVLTree() {
    root = nullptr;
  }

  void insert(const Flight &x) {
    root = insert(x, root);
  }

  void remove(const Flight &x) {
    root = remove(x, root);
  }

  void display() {
    cout << "Number\tCompany\tDeparture Airport\t=>\tArrivalAirport\tFree Seats\tTotal Seats" << endl;
    postOrder(root);
  }

};
