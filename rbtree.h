#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <iostream>

struct RedBlackKey {
  int key;
  struct RedBlackTreeNode *RBnode;
};

struct RedBlackTreeNode {
  void* key;
  int red;
  struct RedBlackTreeNode *left;
  struct RedBlackTreeNode *right;
  struct RedBlackTreeNode *parent;
};

class RedBlackTree {
 public:
  RedBlackTree ();
  struct RedBlackTreeNode *GetRoot ();
  struct RedBlackTreeNode *GetLeaf ();
  void SetRoot (RedBlackTreeNode* root);
  void InsertColour (struct RedBlackTreeNode *newNode);
  void DeleteNode (struct RedBlackTreeNode *redBlackTreeNode);
  struct RedBlackTreeNode *nil;
  struct RedBlackTreeNode *root;
  void InitialiseSentinel ();
  void InitialiseRoot ();
  int GetRank ();
  RedBlackTreeNode* GetMinimumVal ();
  RedBlackTreeNode* GetMaximumVal ();
  int ExtractMinimum ();
  int ExtractMaximum ();
  void InsertData (int key);
  void LeftRotate (struct RedBlackTreeNode *RBTreeNode);
  void RightRotate (struct RedBlackTreeNode *RBTreeNode);
  struct RedBlackTreeNode *GetSuccessor (struct RedBlackTreeNode *redBlackTreeNode);
  void DeleteFixUp (struct RedBlackTreeNode *x);
};

RedBlackTree* GetMergedRBTree (RedBlackTree* red_black_tree1, RedBlackTree* red_black_tree2, bool is_elements_in_tree1_greater);

RedBlackTree* GetMergeTreeToLeft (RedBlackTree* red_black_tree1, RedBlackTree* red_black_tree2);
RedBlackTree* GetMergeTreeToRight (RedBlackTree* red_black_tree1, RedBlackTree* red_black_tree2);