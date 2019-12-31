#ifndef BST_LIBRARY
#define BST_LIBRARY

#include "./lib.h"

#define ER_EMPTYTREE -1
#define ER_EMPTYNODE -2
#define ER_UNKNWPRNT -3

#define TRUE 1
#define FALSE 0

typedef struct node *BSTptr;

typedef struct node {
	int key;
	BSTptr left, right;
} BSTnode;

typedef struct BST {
	int size;
	BSTptr root;
} BST;

void Insert_node(BST *pBST, int pKey);

void tree_info(BST *pBST);

void Free_tree(BST *pBST);

void Free_node(BST *pBST, BSTptr pNode);

void Get_node(BST *pBST, int pKey, BSTptr *pNode);

#endif
