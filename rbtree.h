#include <stdio.h>
#include <limits.h>
#include <stdlib.h>



struct RedBlackTreeNode
{
  int key;
  int red;
  struct RedBlackTreeNode *left;
  struct RedBlackTreeNode *right;
  struct RedBlackTreeNode *parent;
};

class RedBlackTree
{

public:
  RedBlackTree ();
  void Insert (int key);
  void Delete (int key);
  void PrintTree ();
  struct RedBlackTreeNode * GetRoot ();
  struct RedBlackTreeNode * GetLeaf ();

private:
  const int MIN_INT = -INT_MAX;
  struct RedBlackTreeNode *nil;
  struct RedBlackTreeNode *root;
  void InitialiseSentinel ();
  void InitialiseRoot ();
  void LeftRotate (struct RedBlackTreeNode *RBTreeNode);
  void RightRotate (struct RedBlackTreeNode *RBTreeNode);
  void TreeInsertHelper (struct RedBlackTreeNode *z);
  void InsertNode (struct RedBlackTreeNode *newNode);
  struct RedBlackTreeNode * GetSuccessor (struct RedBlackTreeNode *redBlackTreeNode);
  struct RedBlackTreeNode * GetNode (int key);
  void DeleteFixUp (struct RedBlackTreeNode *x);
  void DeleteNode (struct RedBlackTreeNode *redBlackTreeNode);
  void InOrder (struct RedBlackTreeNode *realRoot);
};
