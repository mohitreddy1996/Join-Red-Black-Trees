/*
* 1) A node is either red or black
* 2) The root is black
* 3) All leaves (NULL) are black
* 4) Both children of every red node are black
* 5) Every simparentle parentath from root to leaves contains the same number
*    of black nodes. 
*/

#include <stdio.h>
#include <stdlib.h>
#define RED		1
#define BLACK	2

struct rb_node {
	int key;
	struct rb_node *left, *right, *parent;
	int color;
};


struct rb_node *NIL;
struct rb_node *NILPTR = (struct rb_node *) &NIL;

void inorder(struct rb_node *x) {
	if (x != NILPTR) {
		inorder(x->left);
		printf("%d -- %d\n", x->key, x->color);
		inorder(x->right);
	}
}

struct rb_node *search(struct rb_node *root, int k) {
    if (root == NULL)
        return root;
	if (root == NILPTR || root->key == k)
		return root;
	if (k < root->key)
		return search(root->left, k);
	else
		return search(root->right, k);
}

void leftrotate(struct rb_node **treeroot, struct rb_node *x) {
	struct rb_node *y = x->right;
	x->right = y->left;
	if (y->left != NILPTR)
		y->left->parent = x;
	y->parent = x->parent;
	if (x->parent == NILPTR)
		*treeroot = y;
	else if (x->parent->left == x)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->left = x;
	x->parent = y;
}

void rightrotate(struct rb_node **treeroot, struct rb_node *y) {
	struct rb_node *x = y->left;
	y->left = x->right;
	if (x->right != NILPTR)
		x->right->parent = y;
	x->parent = y->parent;
	if (y->parent == NILPTR)
		*treeroot = x;
	else if (y->parent->left == y)
		y->parent->left = x;
	else
		y->parent->right = x;
	x->right = y;
	y->parent = x;
}

void rbinsertfixup(struct rb_node **treeroot, struct rb_node *z) {
	while (z->parent!= NILPTR && z->parent->color == RED) {
		if (z->parent->parent != NILPTR && z->parent == z->parent->parent->left) {
			struct rb_node *y = z->parent->parent->right;
			if (y->color == RED) {
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else {
				if (z == z->parent->right) {
					z = z->parent;
					leftrotate(treeroot,z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				rightrotate(treeroot,z->parent->parent);
			}
		}
		else if(z->parent->parent != NILPTR){
			struct rb_node *y = z->parent->parent->left;
			if (y->color == RED) {
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else {
				if (z == z->parent->left) {
					z = z->parent;
					rightrotate(treeroot,z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				leftrotate(treeroot,z->parent->parent);
			}
		}
	}
	(*treeroot)->color = BLACK;
}

void rbinsert(struct rb_node **treeroot, int z) {
	printf("Entering rbinsert\n");
	struct rb_node *Z = (struct rb_node *) malloc(sizeof(struct rb_node));
	Z->key = z;
	struct rb_node *y = NILPTR;
	struct rb_node *x = *treeroot;
	printf("Searching for correct insertion position\n");
	while (x != NILPTR) {
		y = x;
		if (Z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	printf("Ending Search\n");
	Z->parent = y;
	if (y == NILPTR)
		*treeroot = Z;
	else if (Z->key < y->key)
		y->left = Z;
	else
		y->right = Z;
	printf("Assigning Current Node\n");
	Z->left = NILPTR;
	Z->right = NILPTR;
	Z->color = RED;
	printf("Before Insert Fix up!\n");
	rbinsertfixup(treeroot,Z);
}

void recolor(struct rb_node *sibling, struct rb_node *parentNode, struct rb_node **treeroot){
	if(sibling->color == BLACK){
		// check if atleast one of sibling's children is red.
		if((sibling->left != NILPTR && sibling->left->color == RED) || (sibling->right != NILPTR && sibling->right->color == RED)){
			// consider 4 rotation cases.

			// left-left and left-right case
			if(parentNode->left == sibling){
				// left-left case
				if(sibling->left->color == RED){
					sibling->left->color = BLACK;
					rightrotate(treeroot, parentNode);
				}
				// left-right case
				else{
					leftrotate(treeroot, sibling);
					// get new sibling
					sibling = parentNode->left;
					sibling->color = BLACK;
					sibling->left->color = RED;

					rightrotate(treeroot, parentNode);
					sibling->left->color = BLACK;
				}
			}
			// right-right and right-left case
			else{
				// right-right case
				if(sibling->right->color == RED){
					sibling->right->color = BLACK;
					leftrotate(treeroot, parentNode);
				}
				// right-left case
				else{
					// right rotate sibling and exchange color.
					rightrotate(treeroot, sibling);
					// get the new sibling.
					sibling = parentNode->right;
					sibling->color = BLACK;
					sibling->right->color = RED;

					leftrotate(treeroot, parentNode);
					sibling->right->color = BLACK;
				}
			}
		}
		// both the children of sibling are black.
		else{
			// recoloring and recursively going upwards.
			if(parentNode->color == RED){
				parentNode->color = BLACK;
				sibling->color = RED;
			}else{
				sibling->color = RED;
				// recursive call.
				parentNode->color = BLACK;
                if(parentNode != *treeroot) {
                    if (parentNode == parentNode->parent->left) {
                        sibling = parentNode->parent->right;
                    } else {
                        sibling = parentNode->parent->left;
                    }
                    parentNode = parentNode->parent;
                    recolor(sibling, parentNode, treeroot);
                }
			}
		}
	}// sibling is red.
	else{
		// cases to be considered. sibling is right child/ left child of its parent.
		// case 1: sibling is left child of parent.
		if(sibling == parentNode->left){
			sibling->color = BLACK;
			parentNode->color = RED;
			rightrotate(treeroot, parentNode);
			parentNode->color = BLACK;
			parentNode->left->color = RED;
		}
		// case 2: sibling is right child of parent.
		else{
			// color the sibling black and parent rb_node red and rotate left.
			sibling->color = BLACK;
			parentNode->color = RED;
			leftrotate(treeroot, parentNode);
			parentNode->color = BLACK;
			parentNode->right->color = RED;
		}
	}
}

void deleteSafe(struct rb_node **treeroot, struct rb_node *nodeptr){
	int nodeColor = nodeptr->color;
	int nodeChildColor = BLACK;
	struct rb_node *childNode = NILPTR;
	if(nodeptr->left == NILPTR && nodeptr->right == NILPTR){
		nodeChildColor = BLACK;
		childNode = NILPTR;
	}else if(nodeptr->left != NILPTR){
		nodeChildColor = nodeptr->left->color;
		childNode = nodeptr->left;
	}else if(nodeptr->right != NILPTR){
		nodeChildColor = nodeptr->right->color;
		childNode = nodeptr->right;
	}

	struct rb_node *parentNode = nodeptr->parent;

	// case 1. rb_node or child having color red. delete the rb_node and mark it as black.
	if(nodeColor == RED || nodeChildColor == RED){
		// childNode = null case to be handled.
		childNode->parent = parentNode;
		childNode->color = BLACK;
		if(parentNode != NILPTR && parentNode->left == nodeptr){
			parentNode->left = childNode;
		}else if(parentNode != NILPTR){
			parentNode->right = childNode;
		}
        if(nodeptr == *treeroot){
            *treeroot = childNode;
        }
	}else if(nodeptr != *treeroot){
		// current rb_node is double black and it is not root.
		// cases 1) sibling s is black and atleast one of sibling's children are red.
		struct rb_node *sibling;
		if(nodeptr == parentNode->left){
			sibling = parentNode->right;
		}else{
			sibling = parentNode->left;
		}
        if(childNode != NILPTR) {
            childNode->parent = parentNode;
            childNode->color = BLACK;
        }
		if(parentNode->left == nodeptr){
            if(childNode == NILPTR)
			    parentNode->left = childNode;
            else
                parentNode->left = NULL;
		}else{
            if(childNode == NILPTR)
			    parentNode->right = childNode;
            else
                parentNode->right = NULL;
		}
		// recoloring 
		recolor(sibling, parentNode, treeroot);
	}else{
		childNode->color = BLACK;
        *treeroot = childNode;
	}

}

void delete(struct rb_node **root, int z){
	struct rb_node *nodeptr = search(*root, z);
	// not found in the tree.
	if(nodeptr == NULL)
		return;
	if(nodeptr == NILPTR){
		return;
	}

	// solve for the case with 2 children nodes.
	struct rb_node *maxLeftChild;
	if(nodeptr->left != NILPTR && nodeptr->right != NILPTR){
		maxLeftChild = nodeptr->left;
		struct rb_node *nextNode = nodeptr->left;
		while(nextNode!=NILPTR){
			maxLeftChild = nextNode;
			nextNode = nextNode->right;
		}
		// swap values.
		int tempKey = maxLeftChild->key;
		maxLeftChild->key = nodeptr->key;
		nodeptr->key = tempKey;

		// rb_node to be deleted nodeptr;
		nodeptr = maxLeftChild;
	}

	deleteSafe(root, nodeptr);

}

int main()
{
    
    int a[] = {4, 2, 1, 5, 6, 3};
    int del[] = {4, 1, 3, 6, 5, 2};
    int i;

    struct rb_node *root;
    root = NILPTR;
    for(i=0; i<6; i++){
    	printf("Loop!\n");
    	rbinsert(&root, a[i]);
    }

    printf("Insertion Done!!!\n");

    inorder(root);

    printf("Deletion Start\n");
    for(i = 0; i<6; i++){
    	delete(&root, del[i]);
    	printf("\n");
    	inorder(root);
    }

    return 0;

}