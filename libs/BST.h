#ifndef BST_LIBRARY
#define BST_LIBRARY

#include "./lib.h"

typedef struct node *BSTptr;

typedef struct node {
	int key;
	BSTptr left, right;
} BSTnode;

typedef struct BST {
	int size;
	BSTptr root;
} BST;

void insertBSTNodeInBST(BST *pBST, int pKey);

void createBST(BST *pBST, BSTptr *pRoot, BSTptr pNode, int pKey);

void printBST(BST *pBST);

void printBSTInOrderTraversal(BSTptr pNode);

void freeBSTNode(BSTptr pNode);

void freeBST(BST *pBST);

BSTptr getBSTNodeInSubBSTByKey(BSTptr pNode, int pKey);

BSTptr getBSTNodeInBSTByKey(BST *pBST, int pKey);

BSTptr getMinimalBSTNodeInSubBST(BSTptr pNode);

BSTptr getMinimalBSTNodeInBST(BST *pBST);

BSTptr getMaximalBSTNodeInSubBST(BSTptr pNode);

BSTptr getMaximalBSTNodeInBST(BST *pBST);

BSTptr getParentOfBSTNodeByKey(BST *pBST, int pKey);

BSTptr getParentOfBSTNode(BSTptr pParent, BSTptr pNode);

void deleteBSTNodeFromBST(BST *pBST, BSTptr pNode);

#endif
