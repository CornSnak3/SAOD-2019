#ifndef SAOD_AVLTREE_H
#define SAOD_AVLTREE_H

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "ConsoleTable.h"
#include "Flight.h"

class AVLTree {

public:

  struct TreeNode {
    Flight data;
    TreeNode *left;
    TreeNode *right;
    int height;
  };

  AVLTree  (ConsoleTable*);
  ~AVLTree (void);

  void      addPostOrder (void);
  void      addPostOrder (TreeNode*);
  bool      remove       (std::string&);
  TreeNode* removeRoot   (void);
  void      insert       (Flight&);
  void      removeAll    (void);
  void      printTree    (void);

  void displaySearchByNumber(std::string&);
  void displaySearchByPattern(std::string&);


private:

  ConsoleTable* linkedTable_;

  TreeNode* root_;

  void      makeEmpty         (TreeNode*);
  TreeNode* insert            (Flight&, TreeNode*);
  TreeNode* singleRightRotate (TreeNode*);
  TreeNode* singleLeftRotate  (TreeNode*);
  TreeNode* doubleRightRotate (TreeNode*);
  TreeNode* doubleLeftRotate  (TreeNode*);
  TreeNode* findMin           (TreeNode*);
  TreeNode* findMax           (TreeNode*);
  TreeNode* remove            (std::string&, TreeNode*);
  int       height            (TreeNode*);
  int       getBalance        (TreeNode*);
  
  void      postOrder         (TreeNode*, std::vector<Flight>*);
  void      postOrder         (TreeNode*, std::string, std::vector<Flight>*);

  void      printTree         (TreeNode*, int);

  void                 searchByNumber  (std::string&, TreeNode*, std::vector<Flight>*);
  std::vector<Flight>* searchByPattern (std::string&);

};

#endif // SAOD_AVLTREE_H