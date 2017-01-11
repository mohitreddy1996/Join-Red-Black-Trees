#include "rbtree.h"

void RedBlackTree::InitialiseSentinel(){
    nil = (struct RedBlackTreeNode *)malloc(sizeof(struct RedBlackTreeNode));
    nil->parent = nil->right = nil->left = nil;
    nil->key = MIN_INT;
    nil->red = 0;
}

void RedBlackTree::InitialiseRoot(){
    root = (struct RedBlackTreeNode *)malloc(sizeof(struct RedBlackTreeNode));
    root->parent = root->right = root->left = nil;
    root->key = INT_MAX;
    root->red = 0;
}

void RedBlackTree::LeftRotate(struct RedBlackTreeNode *RBTreeNode)
{
    struct RedBlackTreeNode *x;
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

void RedBlackTree::RightRotate(struct RedBlackTreeNode *RBTreeNode)
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

void RedBlackTree::TreeInsertHelper(struct RedBlackTreeNode *z) {
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


void RedBlackTree::InsertNode(struct RedBlackTreeNode *newNode)
{
    struct RedBlackTreeNode *y;
    struct RedBlackTreeNode *x;

    x = newNode;
    TreeInsertHelper(x);
    x->red = 1;
    while (x->parent->red){
        if(x->parent == x->parent->parent->left){
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
    root->left->red = 0;
    return;
}

void RedBlackTree::Insert(int key)
{
    struct RedBlackTreeNode *newNode = (struct RedBlackTreeNode *)malloc(sizeof(struct RedBlackTreeNode));
    newNode->key = key;
    newNode->parent = newNode->right = newNode->left = nil;

    return InsertNode(newNode);
}

struct RedBlackTreeNode* RedBlackTree::GetSuccessor(struct RedBlackTreeNode *redBlackTreeNode){
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
        if(y == root){
            return nil;
        }
        return y;
    }
}

struct RedBlackTreeNode* RedBlackTree::GetNode(int key){
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

void RedBlackTree::DeleteFixUp(struct RedBlackTreeNode *x){
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


void RedBlackTree::DeleteNode(struct RedBlackTreeNode *redBlackTreeNode){
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
            DeleteFixUp(x);
        }else{
            y->red = redBlackTreeNode->red;
        }
    }else{
        if(!(y->red)){
            DeleteFixUp(x);
        }
    }

}

void RedBlackTree::Delete(int key){
    struct RedBlackTreeNode *node;
    node = GetNode(key);
    DeleteNode(node);
}

void RedBlackTree::InOrder(struct RedBlackTreeNode *realRoot){
    if(realRoot != nil){
        InOrder(realRoot->left);
        printf("Key - %d :: Color - %d\n", realRoot->key, realRoot->red);
        InOrder(realRoot->right);
    }
}
void RedBlackTree::PrintTree(){
    struct RedBlackTreeNode *rootLeft = root->left;
    InOrder(rootLeft);
}


int main(){
    RedBlackTree rb;
    rb.InitialiseSentinel();
    rb.InitialiseRoot();

    int input[] = {6, 5, 4, 3, 2, 1};
    int delSeq[] = {2, 3, 1, 4, 5, 6};
    int iter = 0;
    for(iter = 0; iter < 6; iter++){
        rb.Insert(input[iter]);
    }

    rb.PrintTree();
    printf("\n---\n");
    for(iter = 0; iter < 6; iter++){
        rb.Delete(delSeq[iter]);
        rb.PrintTree();
        printf("\n -------- \n");
    }
    return 0;
}
