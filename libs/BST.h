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

void BSTInsertNode(BST *pBST, int pKey);

void BSTBinarySearchVacancy(BST *pBST, BSTptr *pRoot, BSTptr pNode, int pKey);

void BSTCreateNode(BSTptr *pRoot, BSTptr pNode, int pKey);

void BSTCreate(BST *pBST, BSTptr *pRoot, BSTptr pNode, int pKey);

void BSTWalk(BST *pBST);

void BSTInOrderTraversal(BSTptr pNode);

void printBST(BST *pBST);

void printBSTInOrderTraversal(BSTptr pNode);

void freeNode(BSTptr pNode);

void freeBST(BST *pBST);

BSTptr searchNode(BSTptr pNode, int pKey);

BSTptr searchBST(BST *pBST, int pKey);

BSTptr searchMinimalSubBST(BSTptr pNode);

BSTptr searchMaximumSubBST(BSTptr pNode);

BSTptr searchMinimalBST(BST *pBST);

BSTptr searchMaximumBST(BST *pBST);

BSTptr getParentNode(BSTptr pParent, BSTptr pNode);

BSTptr getParentNodeFromBST(BST *pBST, int pKey);

void case_B(BST *pBST, BSTptr pNode, BSTptr pParent);

void case_C(BST *pBST, BSTptr pNode, BSTptr pParent);

void case_A(BST *pBST, BSTptr pNode, BSTptr pParent);

void deleteNode(BST *pBST, int pKey);

#endif
