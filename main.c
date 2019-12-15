#include <stdio.h>
#include <math.h>
#include "./libs/lib.h"
#include "./libs/BST.h"

int main (int argc, char *argv[]) {
	BST pBST = {0, NULL};
	BSTptr pNode;
	BSTptr pParent;
	
	pBST.root = NULL;
	insertBSTNodeInBST(&pBST, 2);
	insertBSTNodeInBST(&pBST, 3);
	insertBSTNodeInBST(&pBST, 5);
	insertBSTNodeInBST(&pBST, 4);
	insertBSTNodeInBST(&pBST, 1);
	insertBSTNodeInBST(&pBST, 6);
	printBST(&pBST);
	pNode = getBSTNodeInBSTByKey(&pBST, 2);
	print_line(STDOUT_FILENO, "node: [%d].\n", pNode->key);
	
	pParent = getParentOfBSTNodeByKey(&pBST, 3);
	if (pParent != NULL) {
		print_line(STDOUT_FILENO, "parent: [%d].\n", pParent->key);
	}
	print_line(STDOUT_FILENO, "Delete.\n");
	//deleteNode(&_BST, 6);
	deleteBSTNodeFromBSTByKey(&pBST, 2);
	deleteBSTNodeFromBSTByKey(&pBST, 5);
	printBST(&pBST);
	freeBST(&pBST);
	return 0;
}
