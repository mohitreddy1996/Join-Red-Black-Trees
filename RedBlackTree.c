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
    nil = (struct RedBlackTreeNode *)malloc(sizeof(struct RedBlackTreeNode));
    nil->parent = nil->right = nil->left = nil;
    nil->key = MIN_INT;
    // Sentinets/Null (Children of leaf nodes are black).
    nil->red = 0;
}

void InitialiseRoot(){
    root = (struct RedBlackTreeNode *)malloc(sizeof(struct RedBlackTreeNode));
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
    x = RBTreeNode->right;
    RBTreeNode->right = x->left;

    if(x->left != nil) {
        x->left->parent = RBTreeNode;
    }

    x->parent = RBTreeNode->parent;
    if(RBTreeNode == RBTreeNode->parent->left) {
        RBTreeNode->parent->left = x;
    }else {
        RBTreeNode->parent->right = x;
    }
    x->left = RBTreeNode;
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


/**
 * Insertion Code.
 * */
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

    return InsertNode(newNode);
}


/**
 * Deletion and Deletion related codes.
 * 1) Delete Node.
 * 2) Search Node.
 * 3) Successor of a Node.
 * 4) Deletion Helper/Fix up (Coloring and Rotation).
 * */

struct RedBlackTreeNode *GetSuccessor(struct RedBlackTreeNode *redBlackTreeNode){
    struct RedBlackTreeNode *y;
    y = redBlackTreeNode->right;

    if(y != nil){
        while(y->left != nil){
            y = y->left;
        }
        return y;
    } else{
        y = redBlackTreeNode->parent;
        while(redBlackTreeNode == y->right){
            redBlackTreeNode = y;
            y = y->parent;
        }
        // because root in this case is a dummy node. No successor present in the tree.
        if(y == root){
            return nil;
        }
        return y;
    }
}

struct RedBlackTreeNode *GetNode(int key){
    struct RedBlackTreeNode *y = root->left;
    while(y != nil){
        if(y->key == key){
            return y;
        }else if(y->key > key){
            y = y->left;
        }else{
            y = y->right;
        }
    }
    return nil;
}

void DeleteFixUp(struct RedBlackTreeNode *x){
    struct RedBlackTreeNode *w;
    struct RedBlackTreeNode *rootLeft = root->left;

    while((!x->red) && (rootLeft != x)){
        if(x == x->parent->left){
            w = x->parent->right;
            if(w->red){
                w->red = 0;
                x->parent->red = 1;
                LeftRotate(x->parent);
                w = x->parent->right;
            }
            if((!w->right->red) && (!w->left->red)){
                w->red = 1;
                x = x->parent;
            }else{
                if(!w->right->red){
                    w->left->red = 0;
                    w->red = 1;
                    RightRotate(w);
                    w = x->parent->right;
                }
                w->red = x->parent->red;
                x->parent->red = 0;
                w->right->red = 0;
                LeftRotate(x->parent);
                x = rootLeft;
            }
        }else{
            /**
             * Symmetric case.
             * */
            w = x->parent->left;
            if(w->red){
                w->red = 0;
                x->parent->red = 1;
                RightRotate(x->parent);
                w = x->parent->left;
            }
            if((!w->right->red) && (!w->left->red)){
                w->red = 1;
                x = x->parent;
            } else{
                if(!w->left->red){
                    w->right->red = 0;
                    w->red = 1;
                    LeftRotate(w);
                    w = x->parent->left;
                }
                w->red = x->parent->red;
                x->parent->red = 0;
                w->left->red = 0;
                RightRotate(x->parent);
                x = rootLeft;
            }
        }
    }
    x->red = 0;
}


void DeleteNode(struct RedBlackTreeNode *redBlackTreeNode){
    struct RedBlackTreeNode *y;
    struct RedBlackTreeNode *x;

    y = ((redBlackTreeNode->left == nil) || (redBlackTreeNode->right == nil)) ? redBlackTreeNode : GetSuccessor(redBlackTreeNode);

    x = (y->left == nil) ? y->right : y->left;

    x->parent = y->parent;
    if(root == x->parent){
        root->left = x;
    }else{
        if(y == y->parent->left){
            y->parent->left = x;
        }else{
            y->parent->right = x;
        }
    }

    if(y != redBlackTreeNode){
        // y has to be taken out.
        y->left = redBlackTreeNode->left;
        y->right = redBlackTreeNode->right;
        y->parent = redBlackTreeNode->parent;

        redBlackTreeNode->left->parent = redBlackTreeNode->right->parent = y;

        if(redBlackTreeNode == redBlackTreeNode->parent->left){
            redBlackTreeNode->parent->left = y;
        }else{
            redBlackTreeNode->parent->right = y;
        }
        if(!(y->red)){
            y->red = redBlackTreeNode->red;
            // Delete Fixup.
            DeleteFixUp(x);
        }else{
            y->red = redBlackTreeNode->red;
        }

        // Assumption checks and Check for nil color. Why?
    }else{
        if(!(y->red)){
            // Delete Fixup.
            DeleteFixUp(x);
        }

        // Assumption checks and Check for nil color. Why?
    }

}

void Delete(int key){
    struct RedBlackTreeNode *node;
    node = GetNode(key);
    DeleteNode(node);
}


/**
 * Util Functions.
 * InOrder Function.
 * */

void InOrder(struct RedBlackTreeNode *realRoot){
    if(realRoot != nil){
        InOrder(realRoot->left);
        printf("Key - %d :: Color - %d\n", realRoot->key, realRoot->red);
        InOrder(realRoot->right);
    }
}
void PrintTree(){
    struct RedBlackTreeNode *rootLeft = root->left;
    InOrder(rootLeft);
}


int main(){
    InitialiseSentinel();
    InitialiseRoot();

    int input[] = {6, 5, 4, 3, 2, 1};
    int delSeq[] = {2, 3, 1, 4, 5, 6};
    int iter = 0;
    for(iter = 0; iter < 6; iter++){
        Insert(input[iter]);
        //PrintTree();
        //printf("\n---\n");
    }

    // print inorder values.
    PrintTree();
    printf("\n---\n");
    for(iter = 0; iter < 6; iter++){
        Delete(delSeq[iter]);
        PrintTree();
        printf("\n -------- \n");
    }
    return 0;
}