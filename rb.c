/*
*  1) A node is either red or black
*  2) The root is black
*  3) All leaves (NULL) are black
*  4) Both children of every red node are black
*  5) Every simparentle parentath from root to leaves contains the same number
*     of black nodes. 
*/

#include <stdio.h>
#include <stdlib.h>
#define RED		1
#define BLACK	2

struct node {
	int key;
	struct node *left, *right, *p;
	int color;
};


typedef struct node *NODEPTR;
struct node NIL;
NODEPTR NILPTR = &NIL;

void inorder(NODEPTR x) {
	if (x != NILPTR) {
		inorder(x->left);
		printf("%d -- %d\n", x->key, x->color);
		inorder(x->right);
	}
}

NODEPTR search(NODEPTR root, int k) {
    if (root == NULL)
        return root;
	if (root == NILPTR || root->key == k)
		return root;
	if (k < root->key)
		return search(root->left, k);
	else
		return search(root->right, k);
}

NODEPTR minimum(NODEPTR root) {
	while (root->left != NILPTR)
		root = root->left;
	return root;
}


void leftrotate(NODEPTR *treeroot, NODEPTR x) {
	NODEPTR y = x->right;
	x->right = y->left;
	if (y->left != NILPTR)
		y->left->p = x;
	y->p = x->p;
	if (x->p == NILPTR)
		*treeroot = y;
	else if (x->p->left == x)
		x->p->left = y;
	else
		x->p->right = y;
	y->left = x;
	x->p = y;
}

void rightrotate(NODEPTR *treeroot, NODEPTR y) {
	NODEPTR x = y->left;
	y->left = x->right;
	if (x->right != NILPTR)
		x->right->p = y;
	x->p = y->p;
	if (y->p == NILPTR)
		*treeroot = x;
	else if (y->p->left == y)
		y->p->left = x;
	else
		y->p->right = x;
	x->right = y;
	y->p = x;
}

void rbinsertfixup(NODEPTR *treeroot, NODEPTR z) {
	while (z->p!= NILPTR && z->p->color == RED) {
		if (z->p->p != NILPTR && z->p == z->p->p->left) {
			NODEPTR y = z->p->p->right;
			if (y->color == RED) {
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else {
				if (z == z->p->right) {
					z = z->p;
					leftrotate(treeroot,z);
				}
				z->p->color = BLACK;
				z->p->p->color = RED;
				rightrotate(treeroot,z->p->p);
			}
		}
		else if(z->p->p != NILPTR){
			NODEPTR y = z->p->p->left;
			if (y->color == RED) {
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else {
				if (z == z->p->left) {
					z = z->p;
					rightrotate(treeroot,z);
				}
				z->p->color = BLACK;
				z->p->p->color = RED;
				leftrotate(treeroot,z->p->p);
			}
		}
	}
	(*treeroot)->color = BLACK;
}

void rbinsert(NODEPTR *treeroot, int z) {
	printf("Entering rbinsert\n");
	NODEPTR Z = (NODEPTR) malloc(sizeof(struct node));
	Z->key = z;
	NODEPTR y = NILPTR;
	NODEPTR x = *treeroot;
	printf("Searching for correct insertion position\n");
	while (x != NILPTR) {
		y = x;
		if (Z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	printf("Ending Search\n");
	Z->p = y;
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

void rbtransplant(NODEPTR *treeroot, NODEPTR u, NODEPTR v) {
	if (u->p == NILPTR)
		*treeroot = u;
	else if (u == u->p->left)
		u->p->left = v;
	else
		u->p->right = v;
	v->p = u->p;
}

void rbdeletefixup(NODEPTR *treeroot, NODEPTR x) {
	while (x != *treeroot && x->color == BLACK) {
		if (x->p!=NILPTR && x == x->p->left) {
			NODEPTR w = x->p->right;
			if (w!=NILPTR && w->color == RED) {
				w->color = BLACK;
				x->p->color = RED;
				leftrotate(treeroot,x->p);
				w = x->p->right;
			}
			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->p;
			}
			else {
			 	if (w->right->color == BLACK) {
					w->left->color = BLACK;
					w->color = RED;
					rightrotate(treeroot,w);
					w = x->p->right;
				}
				w->color = x->p->color;
				x->p->color = BLACK;
				w->right->color = BLACK;
				leftrotate(treeroot,x->p);
				x = *treeroot;
			}
		}
		else if(x->p!=NILPTR){
			NODEPTR w = x->p->left;
			if (w->color == RED) {
				w->color = BLACK;
				x->p->color = RED;
				rightrotate(treeroot,x->p);
				w = x->p->left;
			}
			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->p;
			}
			else {
				if (w->left->color == BLACK) {
					w->right->color = BLACK;
					w->color = RED;
					leftrotate(treeroot,w);
					w = x->p->left;
				}
				w->color = x->p->color;
				x->p->color = BLACK;
				w->left->color = BLACK;
				rightrotate(treeroot,x->p);
				x = *treeroot;
			}
		}
	}
	x->color = BLACK;
}

void recolor(NODEPTR sibling, NODEPTR parentNode, NODEPTR *treeroot){
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
                    if (parentNode == parentNode->p->left) {
                        sibling = parentNode->p->right;
                    } else {
                        sibling = parentNode->p->left;
                    }
                    parentNode = parentNode->p;
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
			// color the sibling black and parent node red and rotate left.
			sibling->color = BLACK;
			parentNode->color = RED;
			leftrotate(treeroot, parentNode);
			parentNode->color = BLACK;
			parentNode->right->color = RED;
		}
	}
}

void deleteSafe(NODEPTR *treeroot, NODEPTR nodeptr){
	int nodeColor = nodeptr->color;
	int nodeChildColor = BLACK;
	NODEPTR childNode = NILPTR;
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

	NODEPTR parentNode = nodeptr->p;

	// case 1. node or child having color red. delete the node and mark it as black.
	if(nodeColor == RED || nodeChildColor == RED){
		// childNode = null case to be handled.
		childNode->p = parentNode;
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
		// current node is double black and it is not root.
		// cases 1) sibling s is black and atleast one of sibling's children are red.
		NODEPTR sibling;
		if(nodeptr == parentNode->left){
			sibling = parentNode->right;
		}else{
			sibling = parentNode->left;
		}
        if(childNode != NILPTR) {
            childNode->p = parentNode;
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

void delete(NODEPTR *root, int z){
	NODEPTR nodeptr = search(*root, z);
	// not found in the tree.
	if(nodeptr == NULL)
		return;
	if(nodeptr == NILPTR){
		return;
	}

	// solve for the case with 2 children nodes.
	NODEPTR maxLeftChild;
	if(nodeptr->left != NILPTR && nodeptr->right != NILPTR){
		maxLeftChild = nodeptr->left;
		NODEPTR nextNode = nodeptr->left;
		while(nextNode!=NILPTR){
			maxLeftChild = nextNode;
			nextNode = nextNode->right;
		}
		// swap values.
		int tempKey = maxLeftChild->key;
		maxLeftChild->key = nodeptr->key;
		nodeptr->key = tempKey;

		// node to be deleted nodeptr;
		nodeptr = maxLeftChild;
	}

	deleteSafe(root, nodeptr);

}

void rbdelete(NODEPTR *treeroot, int z) {
	//cout<<"qq";
	NODEPTR Z = search(*treeroot, z);
	//cout<<"qq";
	if(Z==NULL)
        return;
	if (Z == NILPTR) {
		//printf("Node to be deleted not found\n");
		return;
	}
	NODEPTR y = Z;
	int yoc = y->color;
	NODEPTR x;
	//cout<<"qq";
	if (Z->left == NILPTR) {
		x = Z->right;
		rbtransplant(treeroot,Z,Z->right);
	}
	else if (Z->right == NILPTR) {
		x = Z->left;
		rbtransplant(treeroot,Z,Z->left);
	}
	else {
		y = minimum(Z->right);
		yoc = y->color;
		x = y->right;
		if (y->p == Z)
			x->p = y;
		else {
			rbtransplant(treeroot,y,y->right);
			y->right = Z->right;
			y->right->p = y;
		}
		rbtransplant(treeroot,Z,y);
		y->left = Z->left;
		y->left->p = y;
		y->color = Z->color;
	}
	if (yoc == BLACK)
		rbdeletefixup(treeroot,x);
}

int main()
{
    
    int a[] = {4, 2, 1, 5, 6, 3};
    int del[] = {4, 1, 3, 6, 5, 2};
    int i;

    NODEPTR root = (NODEPTR)malloc(sizeof(NODEPTR));
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