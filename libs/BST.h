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

void getVacancyPlaceForBSTNodeInBST(BST *pBST, BSTptr *pRoot, BSTptr pNode, int pKey);

void createBSTNodeInBST(BSTptr *pRoot, BSTptr pNode, int pKey);

void createBST(BST *pBST, BSTptr *pRoot, BSTptr pNode, int pKey);

void BSTWalk(BST *pBST);

void BSTInOrderTraversal(BSTptr pNode);

void printBST(BST *pBST);

void printBSTInOrderTraversal(BSTptr pNode);

void freeBSTNode(BSTptr pNode);

void freeBST(BST *pBST);

void deleteBSTNodeFromBST(BST *pBST, BSTptr pNode);

BSTptr getBSTNodeInSubBSTByKey(BSTptr pNode, int pKey);

BSTptr getBSTNodeInBSTByKey(BST *pBST, int pKey);

BSTptr getMinimalBSTNodeInSubBST(BSTptr pNode);

BSTptr getMaximalBSTNodeInSubBST(BSTptr pNode);

BSTptr getMinimalBSTNodeInBST(BST *pBST);

BSTptr getMaximalBSTNodeInBST(BST *pBST);

BSTptr getParentOfBSTNode(BSTptr pParent, BSTptr pNode);

BSTptr getParentOfBSTNodeByKey(BST *pBST, int pKey);

#endif
