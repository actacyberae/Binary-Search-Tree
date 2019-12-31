#include <stdio.h>
#include <math.h>
#include "./libs/lib.h"
#include "./libs/BST.h"

int main (int argc, char *argv[]) {
	BST pBST = {0, NULL};
	BSTptr pNode;
	Insert_node(&pBST, 40);
	Insert_node(&pBST, 30);
	Insert_node(&pBST, 35);
	Insert_node(&pBST, 34);
	Insert_node(&pBST, 32);
	Insert_node(&pBST, 25);
	Insert_node(&pBST, 1);
	Insert_node(&pBST, 27);
	Insert_node(&pBST, 26);
	Insert_node(&pBST, 28);
	Insert_node(&pBST, 60);
	Insert_node(&pBST, 50);
	Insert_node(&pBST, 47);
	Insert_node(&pBST, 55);
	Insert_node(&pBST, 57);
	Insert_node(&pBST, 52);
	Insert_node(&pBST, 54);
	Insert_node(&pBST, 53);
	Insert_node(&pBST, 70);
	Insert_node(&pBST, 65);
	Insert_node(&pBST, 75);
	tree_info(&pBST);
	
	
	print_line(STDOUT_FILENO, "========\n");
	Get_node(&pBST, 25, &pNode);
	print_line(STDOUT_FILENO, "DELETE NODE: [%d]\n", pNode->key);
	print_line(STDOUT_FILENO, "========\n");
	Free_node(&pBST, pNode);
	tree_info(&pBST);
	
	print_line(STDOUT_FILENO, "========\n");
	Get_node(&pBST, 75, &pNode);
	print_line(STDOUT_FILENO, "DELETE NODE: [%d]\n", pNode->key);
	print_line(STDOUT_FILENO, "========\n");
	Free_node(&pBST, pNode);
	tree_info(&pBST);
	
	print_line(STDOUT_FILENO, "========\n");
	Get_node(&pBST, 34, &pNode);
	print_line(STDOUT_FILENO, "DELETE NODE: [%d]\n", pNode->key);
	print_line(STDOUT_FILENO, "========\n");
	Free_node(&pBST, pNode);
	tree_info(&pBST);
	
	print_line(STDOUT_FILENO, "========\n");
	Get_node(&pBST, 32, &pNode);
	print_line(STDOUT_FILENO, "DELETE NODE: [%d]\n", pNode->key);
	print_line(STDOUT_FILENO, "========\n");
	Free_node(&pBST, pNode);
	tree_info(&pBST);
	
	print_line(STDOUT_FILENO, "========\n");
	Get_node(&pBST, 1, &pNode);
	print_line(STDOUT_FILENO, "DELETE NODE: [%d]\n", pNode->key);
	print_line(STDOUT_FILENO, "========\n");
	Free_node(&pBST, pNode);
	tree_info(&pBST);
	
	
	print_line(STDOUT_FILENO, "========\n");
	Get_node(&pBST, 33, &pNode);
	
	print_line(STDOUT_FILENO, "========\n");
	Free_node(&pBST, pNode);
	tree_info(&pBST);
	
	print_line(STDOUT_FILENO, "Exit\n");
	Free_tree(&pBST);
	
	return 0;
}
