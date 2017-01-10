//
// Created by mohit on 10/1/17.
//

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

const int MIN_INT = -INT_MAX;

struct RedBlackTreeNode{
    int key;
    /**
     * red = 0, colored black.
     * red = 1, colored red.
     * */
    int red;
    struct RedBlackTreeNode *left;
    struct RedBlackTreeNode *right;
    struct RedBlackTreeNode *parent;
};

// sentinel.
struct RedBlackTreeNode *nil;
struct RedBlackTreeNode *root;

void InitialiseSentinel(){
    nil->parent = nil->right = nil->left = nil;
    nil->key = MIN_INT;
    // Sentinets/Null (Children of leaf nodes are black).
    nil->red = 0;
}

void InitialiseRoot(){
    root->parent = root->right = root->left = nil;
    root->key = INT_MAX;
    // root is always black.
    root->red = 0;
}

/**
 * Input : Node to at which rotation takes place.
 *
 * Output ; None.
 *
 * Effects : Left Rotate used to balance the height at node RBTreeNode.
 *
 * */
void LeftRotate(struct RedBlackTreeNode *RBTreeNode)
{
    struct RedBlackTreeNode *x;
    // taking sentinel takes care of most of the NULL affected codes.
    x = RBTreeNode->left;
    RBTreeNode->left = x->right;

    if(x->right != nil) {
        x->right->parent = RBTreeNode;
    }

    x->parent = RBTreeNode->parent;
    if(RBTreeNode == RBTreeNode->parent->left) {
        RBTreeNode->parent->left = x;
    }else {
        RBTreeNode->parent->right = x;
    }
    x->right = RBTreeNode;
    RBTreeNode->parent = x;
}

void RightRotate(struct RedBlackTreeNode *RBTreeNode)
{
    struct RedBlackTreeNode *x;
    x = RBTreeNode->left;
    RBTreeNode->left = x->right;

    if(x->right != nil) {
        x->right->parent = RBTreeNode;
    }

    x->parent = RBTreeNode->parent;

    if(RBTreeNode == RBTreeNode->parent->left) {
        RBTreeNode->parent->left = x;
    } else {
        RBTreeNode->parent->right = x;
    }
    x->right = RBTreeNode;
    RBTreeNode->parent = x;
}

void TreeInsertHelper(struct RedBlackTreeNode *z) {
    struct RedBlackTreeNode *x;
    struct RedBlackTreeNode *y;

    z->left = z->right = nil;
    y = root;
    x = root->left;

    while (x != nil){
        y = x;
        if(x->key > z->key) {
            x = x->left;
        }else {
            x = x->right;
        }
    }

    z->parent = y;
    if( (y == root) || (y->key > z->key)) {
        y->left = z;
    }else {
        y->right = z;
    }

}


void InsertNode(struct RedBlackTreeNode *newNode)
{
    struct RedBlackTreeNode *y;
    struct RedBlackTreeNode *x;

    x = newNode;
    TreeInsertHelper(x);
    x->red = 1;
    while (x->parent->red){
        if(x->parent == x->parent->parent->left){
            // uncle.
            y = x->parent->parent->right;
            if(y->red){
                x->parent->red = 0;
                y->red = 0;
                x->parent->parent->red = 1;
                x = x->parent->parent;
            }else{
                if(x == x->parent->right){
                    x = x->parent;
                    LeftRotate(x);
                }
                x->parent->red = 0;
                x->parent->parent->red = 1;
                RightRotate(x->parent->parent);
            }
        }else{
            /**
             * Symmetric case.
             * */
             y = x->parent->parent->left;
            if(y->red){
                x->parent->red = 0;
                y->red = 0;
                x->parent->parent->red = 1;
                x = x->parent->parent;
            } else{
                if(x == x->parent->left){
                    x = x->parent;
                    RightRotate(x);
                }
                x->parent->red = 0;
                x->parent->parent->red = 1;
                LeftRotate(x->parent->parent);
            }
        }
    }
    /**
     * Original tree node at Left of the rb tree here.
     * To follow the rule that root is always black.
     * */
    root->left->red = 0;
    return;
}

void Insert(int key)
{
    struct RedBlackTreeNode *newNode = (struct RedBlackTreeNode *)malloc(sizeof(struct RedBlackTreeNode));
    newNode->key = key;
    newNode->parent = newNode->right = newNode->left = nil;
    newNode->red = 1;

    return InsertNode(newNode);
}
