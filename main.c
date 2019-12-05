#include <stdio.h>
#include <math.h>
#include "./libs/lib.h"
#include "./libs/BST.h"

int main (int argc, char *argv[]) {
	BST pBST = {0, NULL};
	BSTptr pNode;
	BSTptr pParent;
	
	pBST.root = NULL;
	BSTInsertNode(&pBST, 2);
	BSTInsertNode(&pBST, 3);
	BSTInsertNode(&pBST, 5);
	BSTInsertNode(&pBST, 4);
	BSTInsertNode(&pBST, 1);
	BSTInsertNode(&pBST, 6);
	printBST(&pBST);
	pNode = searchBST(&pBST, 2);
	print_line(STDOUT_FILENO, "node: [%d].\n", pNode->key);
	
	pParent = getParentNodeFromBST(&pBST, 3);
	if (pParent != NULL) {
		print_line(STDOUT_FILENO, "parent: [%d].\n", pParent->key);
	}
	print_line(STDOUT_FILENO, "Delete.\n");
	//deleteNode(&_BST, 6);
	deleteNode(&pBST, 2);
	deleteNode(&pBST, 5);
	printBST(&pBST);
	freeBST(&pBST);
	return 0;
}
