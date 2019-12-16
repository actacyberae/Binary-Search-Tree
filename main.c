#include <stdio.h>
#include <math.h>
#include "./libs/lib.h"
#include "./libs/BST.h"

int main (int argc, char *argv[]) {
	BST pBST = {0, NULL};
	BSTptr pNode;
	
	insertBSTNodeInBST(&pBST, 40);
	insertBSTNodeInBST(&pBST, 30);
	insertBSTNodeInBST(&pBST, 35);
	insertBSTNodeInBST(&pBST, 31);
	insertBSTNodeInBST(&pBST, 34);
	insertBSTNodeInBST(&pBST, 33);
	insertBSTNodeInBST(&pBST, 25);
	insertBSTNodeInBST(&pBST, 1);
	insertBSTNodeInBST(&pBST, 27);
	insertBSTNodeInBST(&pBST, 26);
	insertBSTNodeInBST(&pBST, 28);
	insertBSTNodeInBST(&pBST, 60);
	insertBSTNodeInBST(&pBST, 50);
	insertBSTNodeInBST(&pBST, 47);
	insertBSTNodeInBST(&pBST, 55);
	insertBSTNodeInBST(&pBST, 57);
	insertBSTNodeInBST(&pBST, 52);
	insertBSTNodeInBST(&pBST, 54);
	insertBSTNodeInBST(&pBST, 53);
	insertBSTNodeInBST(&pBST, 70);
	insertBSTNodeInBST(&pBST, 65);
	insertBSTNodeInBST(&pBST, 75);
	printBST(&pBST);
	print_line(STDOUT_FILENO, "========\n");
	pNode = getBSTNodeInBSTByKey(&pBST, 40);
	print_line(STDOUT_FILENO, "DELETE NODE: [%d]\n", pNode->key);
	print_line(STDOUT_FILENO, "========\n");
	deleteBSTNodeFromBST(&pBST, pNode);
	printBST(&pBST);
	print_line(STDOUT_FILENO, "========\n");
	pNode = getBSTNodeInBSTByKey(&pBST, 60);
	print_line(STDOUT_FILENO, "DELETE NODE: [%d]\n", pNode->key);
	print_line(STDOUT_FILENO, "========\n");
	deleteBSTNodeFromBST(&pBST, pNode);
	printBST(&pBST);
	print_line(STDOUT_FILENO, "========\n");
	pNode = getBSTNodeInBSTByKey(&pBST, 25);
	print_line(STDOUT_FILENO, "DELETE NODE: [%d]\n", pNode->key);
	print_line(STDOUT_FILENO, "========\n");
	deleteBSTNodeFromBST(&pBST, pNode);
	printBST(&pBST);
	print_line(STDOUT_FILENO, "========\n");
	pNode = getBSTNodeInBSTByKey(&pBST, 34);
	print_line(STDOUT_FILENO, "DELETE NODE: [%d]\n", pNode->key);
	print_line(STDOUT_FILENO, "========\n");
	deleteBSTNodeFromBST(&pBST, pNode);
	printBST(&pBST);
	print_line(STDOUT_FILENO, "========\n");
	pNode = getBSTNodeInBSTByKey(&pBST, 52);
	print_line(STDOUT_FILENO, "DELETE NODE: [%d]\n", pNode->key);
	print_line(STDOUT_FILENO, "========\n");
	deleteBSTNodeFromBST(&pBST, pNode);
	printBST(&pBST);
	print_line(STDOUT_FILENO, "========\n");
	pNode = getBSTNodeInBSTByKey(&pBST, 1);
	print_line(STDOUT_FILENO, "DELETE NODE: [%d]\n", pNode->key);
	print_line(STDOUT_FILENO, "========\n");
	deleteBSTNodeFromBST(&pBST, pNode);
	printBST(&pBST);
	print_line(STDOUT_FILENO, "========\n");
	pNode = getBSTNodeInBSTByKey(&pBST, 33);
	print_line(STDOUT_FILENO, "DELETE NODE: [%d]\n", pNode->key);
	print_line(STDOUT_FILENO, "========\n");
	deleteBSTNodeFromBST(&pBST, pNode);
	printBST(&pBST);
	print_line(STDOUT_FILENO, "Exit\n");
	freeBST(&pBST);
	return 0;
}
