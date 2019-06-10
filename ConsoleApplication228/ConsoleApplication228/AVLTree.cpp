#include "AVLTree.h"

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
  node->height = max(height(node->left), height(node->right)) + 1;
  return node;
}

AVLTree::treeNode *AVLTree::singleRightRotate(treeNode * &node) {
  treeNode *u = node->left;
  node->left = u->right;
  u->right = node;
  node->height = max(height(node->left), height(node->right)) + 1;
  u->height = max(height(u->left), node->height) + 1;
  return u;
}

AVLTree::treeNode *AVLTree::singleLeftRotate(treeNode * &node) {
  treeNode *u = node->right;
  node->right = u->left;
  u->left = node;
  node->height = max(height(node->left), height(node->right)) + 1;
  u->height = max(height(node->right), node->height) + 1;
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



AVLTree::AVLTree()
{
}


AVLTree::~AVLTree()
{
}
