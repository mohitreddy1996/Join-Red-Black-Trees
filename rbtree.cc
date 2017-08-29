#include "rbtree.h"

using namespace std;

RedBlackTree::RedBlackTree () {
  InitialiseSentinel ();
  InitialiseRoot ();
}

void RedBlackTree::InitialiseSentinel () {
  nil = (struct RedBlackTreeNode *)malloc (sizeof(struct RedBlackTreeNode));
  nil->parent = nil->right = nil->left = nil;
  nil->key = NULL;
  nil->red = 0;
}

void RedBlackTree::InitialiseRoot () {
  root = (struct RedBlackTreeNode *)malloc (sizeof(struct RedBlackTreeNode));
  root->parent = root->right = root->left = nil;
  root->key = NULL;
  root->red = 0;
}

struct RedBlackTreeNode* RedBlackTree::GetRoot () {
  return root;
}

struct RedBlackTreeNode* RedBlackTree::GetLeaf () {
  return nil;
}

void RedBlackTree::LeftRotate (struct RedBlackTreeNode *RBTreeNode) {
  struct RedBlackTreeNode *x;
  x = RBTreeNode->right;
  RBTreeNode->right = x->left;

  if (x->left != nil) {
    x->left->parent = RBTreeNode;
  }

  x->parent = RBTreeNode->parent;
  if (RBTreeNode == RBTreeNode->parent->left) {
    RBTreeNode->parent->left = x;
  } else {
    RBTreeNode->parent->right = x;
  }
  x->left = RBTreeNode;
  RBTreeNode->parent = x;
}

void RedBlackTree::RightRotate (struct RedBlackTreeNode *RBTreeNode) {
  struct RedBlackTreeNode *x;
  x = RBTreeNode->left;
  RBTreeNode->left = x->right;

  if (x->right != nil) {
    x->right->parent = RBTreeNode;
  }

  x->parent = RBTreeNode->parent;

  if (RBTreeNode == RBTreeNode->parent->left) {
    RBTreeNode->parent->left = x;
  } else {
    RBTreeNode->parent->right = x;
  }
  x->right = RBTreeNode;
  RBTreeNode->parent = x;
}

void RedBlackTree::InsertColour (struct RedBlackTreeNode *newNode) {
  struct RedBlackTreeNode *y;
  struct RedBlackTreeNode *x;

  x = newNode;
  x->red = 1;
  while (x->parent->red) {
    if (x->parent == x->parent->parent->left) {
      y = x->parent->parent->right;
      if (y->red) {
        x->parent->red = 0;
        y->red = 0;
        x->parent->parent->red = 1;
        x = x->parent->parent;
      } else {
        if (x == x->parent->right) {
          x = x->parent;
          LeftRotate (x);
        }
        x->parent->red = 0;
        x->parent->parent->red = 1;
        RightRotate (x->parent->parent);
      }
    } else {
      y = x->parent->parent->left;
      if (y->red) {
        x->parent->red = 0;
        y->red = 0;
        x->parent->parent->red = 1;
        x = x->parent->parent;
      } else {
        if (x == x->parent->left) {
          x = x->parent;
          RightRotate (x);
        }
        x->parent->red = 0;
        x->parent->parent->red = 1;
        LeftRotate (x->parent->parent);
      }
    }
  }
  root->left->red = 0;
  return;
}

struct RedBlackTreeNode* RedBlackTree::GetSuccessor (struct RedBlackTreeNode *redBlackTreeNode) {
  struct RedBlackTreeNode *y;
  y = redBlackTreeNode->right;

  if (y != nil) {
    while (y->left != nil) {
      y = y->left;
    }
    return y;
  } else {
    y = redBlackTreeNode->parent;
    while (redBlackTreeNode == y->right) {
      redBlackTreeNode = y;
      y = y->parent;
    }
    if (y == root) {
      return nil;
    }
    return y;
  }
}

void RedBlackTree::DeleteFixUp (struct RedBlackTreeNode *x)
{
  struct RedBlackTreeNode *w;
  struct RedBlackTreeNode *rootLeft = root->left;

  while ((!x->red) && (rootLeft != x)) {
    if (x == x->parent->left) {
      w = x->parent->right;
      if (w->red) {
        w->red = 0;
        x->parent->red = 1;
        LeftRotate (x->parent);
        w = x->parent->right;
      }
      if ((!w->right->red) && (!w->left->red)) {
        w->red = 1;
        x = x->parent;
      } else {
        if (!w->right->red) {
          w->left->red = 0;
          w->red = 1;
          RightRotate (w);
          w = x->parent->right;
        }
        w->red = x->parent->red;
        x->parent->red = 0;
        w->right->red = 0;
        LeftRotate (x->parent);
        x = rootLeft;
      }
    }
    else {
      w = x->parent->left;
      if (w->red) {
        w->red = 0;
        x->parent->red = 1;
        RightRotate (x->parent);
        w = x->parent->left;
      }
      if ((!w->right->red) && (!w->left->red)) {
        w->red = 1;
        x = x->parent;
      } else {
        if (!w->left->red) {
          w->right->red = 0;
          w->red = 1;
          LeftRotate (w);
          w = x->parent->left;
        }
        w->red = x->parent->red;
        x->parent->red = 0;
        w->left->red = 0;
        RightRotate (x->parent);
        x = rootLeft;
      }
    }
  }
  x->red = 0;
}


void RedBlackTree::DeleteNode (struct RedBlackTreeNode *redBlackTreeNode) {
  struct RedBlackTreeNode *y;
  struct RedBlackTreeNode *x;

  y = ((redBlackTreeNode->left == nil) || (redBlackTreeNode->right == nil)) ? redBlackTreeNode : GetSuccessor (redBlackTreeNode);

  x = (y->left == nil) ? y->right : y->left;

  x->parent = y->parent;
  if (root == x->parent) {
    root->left = x;
  } else {
    if (y == y->parent->left) {
      y->parent->left = x;
    } else {
      y->parent->right = x;
    }
  }

  if (y != redBlackTreeNode) {
    y->left = redBlackTreeNode->left;
    y->right = redBlackTreeNode->right;
    y->parent = redBlackTreeNode->parent;

    redBlackTreeNode->left->parent = redBlackTreeNode->right->parent = y;

    if (redBlackTreeNode == redBlackTreeNode->parent->left) {
      redBlackTreeNode->parent->left = y;
    }
    else {
      redBlackTreeNode->parent->right = y;
    }

    if (!(y->red)) {
      y->red = redBlackTreeNode->red;
      DeleteFixUp (x);
    }
    else {
      y->red = redBlackTreeNode->red;
    }
  } else {
    if (!(y->red)) {
      DeleteFixUp (x);
    }
  }
  free(redBlackTreeNode);
}

// Balanced BST hence the operation is O(logn).
int RedBlackTree::GetRank () {
  RedBlackTreeNode* root = this->GetRoot()->left;
  int count = 0;
  while (root != nil) {
    if (!root->red) {
      count++;
    }
    root = root->left;
  }
  return count;
}

// Balanced BST hence the operation is O(logn).
RedBlackTreeNode* RedBlackTree::GetMinimumVal () {
  RedBlackTreeNode* root = this->GetRoot ()->left;
  while (root->left != nil) {
    root = root->left;
  }
  return root;
}

// Balanced BST hence the operation in O(logn).
RedBlackTreeNode* RedBlackTree::GetMaximumVal () {
  RedBlackTreeNode* root = this->GetRoot ()->left;
  while (root->right != nil) {
    root = root->right;
  }
  return root;
}

int RedBlackTree::ExtractMaximum () {
  RedBlackTreeNode* val = this->GetMaximumVal ();
  int value = ((struct RedBlackKey *)(val->key))->key;
  this->DeleteNode (val);
  return value;
}

int RedBlackTree::ExtractMinimum () {
  RedBlackTreeNode* val = this->GetMinimumVal ();
  int value = ((struct RedBlackKey *)(val->key))->key;
  this->DeleteNode (val);
  return value;
}

RedBlackTree* GetMergeTreeToLeft(RedBlackTree* red_black_tree1, RedBlackTree* red_black_tree2) {
  int rank_rbtree1 = red_black_tree1->GetRank ();
  int rank_rbtree2 = red_black_tree2->GetRank ();
  int val = red_black_tree2->ExtractMaximum ();
  rank_rbtree2 = red_black_tree2->GetRank ();
  int count1 = rank_rbtree1;
  RedBlackTreeNode* root1 = (red_black_tree1->GetRoot())->left;
  while (root1 != red_black_tree1->nil) {
    if (count1 == rank_rbtree2 + 1) {
      break;
    }
    if (root1->red == 0) {
      count1--;
    }
    root1 = root1->left;
  }
  RedBlackTreeNode* orig_left_child = root1->left;
  struct RedBlackKey* rbk = (struct RedBlackKey*)malloc (sizeof(struct RedBlackKey*));
  rbk->key = val;
  struct RedBlackTreeNode *newNode = (struct RedBlackTreeNode *)malloc (sizeof(struct RedBlackTreeNode));
  newNode->key = (void *) rbk;
  newNode->parent = newNode->right = newNode->left = red_black_tree1->GetLeaf ();
  rbk->RBnode  = newNode;
  root1->left = newNode;
  newNode->parent = root1;
  newNode->red = 1;
  newNode->left = (red_black_tree2->GetRoot ())->left;
  // assert (newNode->left != red_black_tree1.nil);
  newNode->left->parent = newNode;
  RedBlackTreeNode* node1 = newNode->left;
  newNode->right = orig_left_child;
  orig_left_child->parent = newNode;
  RedBlackTreeNode* parent = newNode->parent;
  RedBlackTreeNode* sibling = red_black_tree1->nil;
  if (parent != red_black_tree1->GetRoot()) {
    if (newNode == parent->right) {
      sibling = parent->left;
    } else {
      sibling = parent->right;
    }
    if (sibling->red) {
      sibling->red = 0;
      newNode->red = 0;
      parent->red = 1;
      red_black_tree1->InsertColour (parent);
    } else {
      if (newNode->right->red) {
        newNode->parent->red = 1;
        newNode->right->red = 0;
        red_black_tree1->LeftRotate (newNode);
        red_black_tree1->RightRotate (parent);
      }
    }
  }
  return red_black_tree1;
}

void RedBlackTree::SetRoot (RedBlackTreeNode* root) {
  this->root = root;
}

RedBlackTree* GetMergeTreeToRight (RedBlackTree* red_black_tree1, RedBlackTree* red_black_tree2) {
  int rank_rbtree1 = red_black_tree1->GetRank ();
  int rank_rbtree2 = red_black_tree2->GetRank ();
  int val = red_black_tree1->ExtractMinimum ();
  rank_rbtree1 = red_black_tree1->GetRank ();
  int count1 = rank_rbtree2;
  RedBlackTreeNode* root1 = (red_black_tree2->GetRoot())->left;
  while (root1 != red_black_tree2->nil) {
    if (count1 == rank_rbtree1 + 1) {
      break;
    }
    if (root1->red == 0) {
      count1--;
    }
    root1 = root1->right;
  }
  RedBlackTreeNode* orig_right_child = root1->right;
  struct RedBlackKey* rbk = (struct RedBlackKey*)malloc (sizeof(struct RedBlackKey*));
  rbk->key = val;
  struct RedBlackTreeNode *newNode = (struct RedBlackTreeNode *)malloc (sizeof(struct RedBlackTreeNode));
  newNode->key = (void *) rbk;
  newNode->parent = newNode->right = newNode->left = red_black_tree2->GetLeaf ();
  rbk->RBnode  = newNode;
  root1->right = newNode;
  newNode->parent = root1;
  newNode->red = 1;
  newNode->right = (red_black_tree1->GetRoot ())->left;
  newNode->left = orig_right_child;
  orig_right_child->parent = newNode;
  RedBlackTreeNode* parent = newNode->parent;
  RedBlackTreeNode* sibling;
  if (newNode == parent->left) {
    sibling = parent->right;
  } else {
    sibling = parent->left;
  }
  if (sibling->red) {
    sibling->red = 0;
    newNode->red = 0;
    parent->red = 1;
    red_black_tree2->InsertColour (parent);
  } else {
    if (newNode->left->red) {
      newNode->parent->red = 1;
      newNode->left->red = 0;
      red_black_tree2->RightRotate (newNode);
      red_black_tree2->LeftRotate (parent);
    }
  }
  return red_black_tree2;
}

RedBlackTree* GetMergedRBTree(RedBlackTree* red_black_tree1, RedBlackTree* red_black_tree2, bool is_elements_in_tree1_greater) {
  RedBlackTree* join_red_black_tree;
  int rank_rbtree1 = red_black_tree1->GetRank ();
  int rank_rbtree2 = red_black_tree2->GetRank ();
  // Elements of red_black_tree1 is greater than red_black_tree2.
  if (is_elements_in_tree1_greater) {
    // Rank of red_black_tree1 is greater than red_black_tree2.
    if (rank_rbtree1 > rank_rbtree2) {
      // Method: Extract maximum from red_black_tree2. Move on the left spine of red_black_tree1 till there are rank_red_black_tree2.
      // Place the vertex to the left child of the node and place the rbtree as left child of the vertex and place the original left 
      // child as right child of the vertex.
      join_red_black_tree = GetMergeTreeToLeft (red_black_tree1, red_black_tree2);
    } else {
      // Rank of red_back_tree1 is lesser than red_black_tree2.

      // Extract minimum from rbtree1. Move on the right spine till the node down which the number of black nodes = rank of rbtree1.
      // Place the vertex as right child, place the original right child as the left child of the vertex and place rbtree1 as right 
      // child as of the vertex.
      join_red_black_tree = GetMergeTreeToRight (red_black_tree1, red_black_tree2);
    }
  } else {
    // Elements of red_black_tree1 is lesser than red_black_tree2.
    if (rank_rbtree1 > rank_rbtree2) {
      // Rank of red_black_tree1 is greater than red_black_tree2.
      // Method same as the case above but with swapping rbtree1 and rbtree2.
      join_red_black_tree = GetMergeTreeToRight (red_black_tree2, red_black_tree1);
    } else {
      // Rank of red_black_tree1 is less than red_black_tree2.
      // Method same as the case above but with swapping rbtree1 and rbtree2.
      join_red_black_tree = GetMergeTreeToLeft (red_black_tree2, red_black_tree1);
    }
  }
  return join_red_black_tree;
}

RedBlackTree rb;

void InOrder (struct RedBlackTreeNode *realRoot) {
  if (realRoot != rb.GetLeaf ()) {
    InOrder (realRoot->left);
    printf ("Key - %d :: Color - %d\n", ((struct RedBlackKey *)(realRoot->key))->key, realRoot->red);
    InOrder (realRoot->right);
  }
}

void PrintTree () {
  cout << "Printing!!\n";
  struct RedBlackTreeNode *rootLeft = (rb.GetRoot ())->left;
  cout << "Inorder starting\n";
  InOrder (rootLeft);
}

void RedBlackTree::InsertData (int key) {
  struct RedBlackKey* rbk = (struct RedBlackKey*)malloc (sizeof(struct RedBlackKey*));
  rbk->key = key;
  struct RedBlackTreeNode *newNode = (struct RedBlackTreeNode *)malloc (sizeof(struct RedBlackTreeNode));
  newNode->key = (void *) rbk;
  newNode->parent = newNode->right = newNode->left = GetLeaf ();
  rbk->RBnode  = newNode;
  struct RedBlackTreeNode *z = newNode;
  struct RedBlackTreeNode *x;
  struct RedBlackTreeNode *y;
  z->left = z->right = GetLeaf ();
  y = GetRoot ();
  x = GetRoot ()->left;
  while (x != GetLeaf ()) {
    y = x;
    if (((struct RedBlackKey *)(x->key))->key > rbk->key) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  z->parent = y;
  if ( (y == GetRoot ()) || (((struct RedBlackKey *)(y->key))->key > rbk->key)) {
    y->left = z;
  } else {
    y->right = z;
  }
  InsertColour (z);
}

/*
int main () {
  int input[] = {6, 5, 4, 3, 2, 1};
  int delSeq[] = {2, 3, 1, 4, 5, 6};
  struct RedBlackKey* rbkarr[6];
  int iter = 0;
  for (iter = 0; iter < 6; iter++) {
    struct RedBlackKey* rbk = (struct RedBlackKey*)malloc (sizeof(struct RedBlackKey*));
    rbk->key = input[iter];
    struct RedBlackTreeNode *newNode = (struct RedBlackTreeNode *)malloc (sizeof(struct RedBlackTreeNode));
    newNode->key = (void *) rbk;
    newNode->parent = newNode->right = newNode->left = rb.GetLeaf ();
    rbk->RBnode  = newNode;
    rbkarr[iter] = rbk;
    struct RedBlackTreeNode *z = newNode;
    struct RedBlackTreeNode *x;
    struct RedBlackTreeNode *y;
    z->left = z->right = rb.GetLeaf ();
    y = rb.GetRoot ();
    x = rb.GetRoot ()->left;
    while (x != rb.GetLeaf ()) {
      y = x;
      if (((struct RedBlackKey *)(x->key))->key > rbk->key) {
        x = x->left;
      } else {
        x = x->right;
      }
    }
    z->parent = y;
    if ( (y == rb.GetRoot ()) || (((struct RedBlackKey *)(y->key))->key > rbk->key)) {
      y->left = z;
    } else {
      y->right = z;
    }
    rb.InsertColour (z);
    // rb.InsertData (input[iter]);
  }
  PrintTree ();
  for (iter = 0; iter < 6; iter++) {
    printf ("----------------------------------\n");
    PrintTree ();
    rb.DeleteNode (rbkarr[delSeq[iter] - 1]->RBnode);
    printf ("----------------------------------\n");
  }
  return 0;
}
*/
