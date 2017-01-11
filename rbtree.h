#include <stdio.h>
#include <limits.h>
#include <stdlib.h>



struct RedBlackTreeNode
{
  void* key;
  int red;
  struct RedBlackTreeNode *left;
  struct RedBlackTreeNode *right;
  struct RedBlackTreeNode *parent;
};

class RedBlackTree
{
public:
  RedBlackTree ();
  struct RedBlackTreeNode * GetRoot ();
  struct RedBlackTreeNode * GetLeaf ();
  void InsertColour (struct RedBlackTreeNode *newNode);
  void DeleteNode (struct RedBlackTreeNode *redBlackTreeNode);
private:
  const int MIN_INT = -INT_MAX;
  struct RedBlackTreeNode *nil;
  struct RedBlackTreeNode *root;
  void InitialiseSentinel ();
  void InitialiseRoot ();
  void LeftRotate (struct RedBlackTreeNode *RBTreeNode);
  void RightRotate (struct RedBlackTreeNode *RBTreeNode);
  struct RedBlackTreeNode * GetSuccessor (struct RedBlackTreeNode *redBlackTreeNode);
  void DeleteFixUp (struct RedBlackTreeNode *x);
};
