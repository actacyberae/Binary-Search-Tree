#include "./BST.h"

static void createBSTNodeInBST(BSTptr *pRoot, BSTptr pNode, int pKey) {
	pNode = *pRoot = (BSTptr) malloc(sizeof(BSTnode));
	pNode->key = pKey;
	pNode->left = pNode->right = NULL;
}

void createBST(BST *pBST, BSTptr *pRoot, BSTptr pNode, int pKey) {
	createBSTNodeInBST(pRoot, pNode, pKey);
	pBST->size++;
}

static void getVacancyPlaceForBSTNodeInBST(BST *pBST, BSTptr *pRoot, BSTptr pNode, int pKey) {
	while (1) {
		if (pNode == NULL) {
			createBST(pBST, pRoot, pNode, pKey);
			break;
		} else if (pKey < pNode->key) {
			pRoot = &pNode->left;
			pNode = pNode->left;
		} else {
			pRoot = &pNode->right;
			pNode = pNode->right;
		}
	}
}

void insertBSTNodeInBST(BST *pBST, int pKey) {
	getVacancyPlaceForBSTNodeInBST(pBST, &pBST->root, pBST->root, pKey);
}

void printBST(BST *pBST) {
	printBSTInOrderTraversal(pBST->root);
}

void printBSTInOrderTraversal(BSTptr pNode) {
	if (pNode != NULL) {
		printBSTInOrderTraversal(pNode->left);
		print_line(STDOUT_FILENO, "[");
		if (pNode->left != NULL) {
			print_line(STDOUT_FILENO, "%d|", (pNode->left)->key);
		} else {
			print_line(STDOUT_FILENO, "NULL|");
		}
		print_line(STDOUT_FILENO, "%d", pNode->key);
		if (pNode->right != NULL) {
			print_line(STDOUT_FILENO, "|%d", (pNode->right)->key);
		} else {
			print_line(STDOUT_FILENO, "|NULL");
		}
		print_line(STDOUT_FILENO, "]\n");
		printBSTInOrderTraversal(pNode->right);
	}
}

void freeBSTNode(BSTptr pNode) {
	if (pNode != NULL) {
		freeBSTNode(pNode->left);
		freeBSTNode(pNode->right);
		free(pNode);
	}
}

void freeBST(BST *pBST) {
	freeBSTNode(pBST->root);
}

BSTptr getBSTNodeInSubBSTByKey(BSTptr pNode, int pKey) {
	if (pNode != NULL) {
		if (pKey < pNode->key) {
			return getBSTNodeInSubBSTByKey(pNode->left, pKey);
		} else if (pKey > pNode->key) {
			return getBSTNodeInSubBSTByKey(pNode->right, pKey);
		} else {
			return pNode;
		}
	} else {
		return NULL;
	}
}

BSTptr getBSTNodeInBSTByKey(BST *pBST, int pKey) {
	return getBSTNodeInSubBSTByKey(pBST->root, pKey);
}

BSTptr getMinimalBSTNodeInSubBST(BSTptr pNode) {
	if (pNode != NULL) {
		if (pNode->left != NULL) {
			return getMinimalBSTNodeInSubBST(pNode->left);
		} else {
			return pNode;
		}
	} else {
		return NULL;
	}
}

BSTptr getMaximalBSTNodeInSubBST(BSTptr pNode) {
	if (pNode != NULL) {
		if (pNode->right != NULL) {
			return getMaximalBSTNodeInSubBST(pNode->right);
		} else {
			return pNode;
		}
	} else {
		return NULL;
	}
}

BSTptr getMinimalBSTNodeInBST(BST *pBST) {
	return getMinimalBSTNodeInSubBST(pBST->root);
}

BSTptr getMaximalBSTNodeInBST(BST *pBST) {
	return getMaximalBSTNodeInSubBST(pBST->root);
}

BSTptr getParentOfBSTNode(BSTptr pParent, BSTptr pNode) {
	if (pParent != NULL) {
		if (pParent->right == pNode || pParent->left == pNode) {
			return pParent;
		} else {
			if (pParent->key > pNode->key) {
				return getParentOfBSTNode(pParent->left, pNode);
			} else if (pParent->key < pNode->key) {
				return getParentOfBSTNode(pParent->right, pNode);
			} else {
				return NULL;
			}
		}
	} else {
		return NULL;
	}
}

BSTptr getParentOfBSTNodeByKey(BST *pBST, int pKey) {
	BSTptr pNode;

	pNode = getBSTNodeInBSTByKey(pBST, pKey);
	if (pNode != NULL) {
		return getParentOfBSTNode(pBST->root, pNode);
	} else {
		return NULL;
	}
}

static void case_A(BST *pBST, BSTptr pDeletedNode, BSTptr pParentOfDeletedNode) {
	if (pDeletedNode != (pBST->root)) {
		if (pParentOfDeletedNode->right == pDeletedNode) {
			pParentOfDeletedNode->right = NULL;
		} else {
			pParentOfDeletedNode->left = NULL;
		}
	} else {
		pBST->root = NULL;
	}
}

static void case_B(BST *pBST, BSTptr pDeletedNode, BSTptr pParentOfDeletedNode) {
	BSTptr pNewNode;
	
	if (pDeletedNode->left != NULL) {
		pNewNode = pDeletedNode->left;
	} else {
		pNewNode = pDeletedNode->right;
	}
	if (pDeletedNode != (pBST->root)) {
		if (pParentOfDeletedNode->right == pDeletedNode) {
			pParentOfDeletedNode->right = pNewNode;
		} else {
			pParentOfDeletedNode->left = pNewNode;
		}
	} else {
		(pBST->root) = pNewNode;
	}
}

static void case_C(BST *pBST, BSTptr pDeletedNode, BSTptr pParentOfDeletedNode) {
	BSTptr pMinimalNodeOfTree;
	BSTptr pMinimalNodeFromRightSubtreeOfDeletedNode;
	BSTptr pParentOfMinimalNodeFromRightSubtreeOfDeletedNode;
	
	pMinimalNodeFromRightSubtreeOfDeletedNode = getMinimalBSTNodeInSubBST(pDeletedNode->right);
	pParentOfMinimalNodeFromRightSubtreeOfDeletedNode = getParentOfBSTNode(pBST->root, pMinimalNodeFromRightSubtreeOfDeletedNode);
	if (pParentOfMinimalNodeFromRightSubtreeOfDeletedNode != pDeletedNode) {
		pParentOfMinimalNodeFromRightSubtreeOfDeletedNode->left = pMinimalNodeFromRightSubtreeOfDeletedNode->right;
	}
	if (pMinimalNodeFromRightSubtreeOfDeletedNode != pDeletedNode->right) {
		pMinimalNodeFromRightSubtreeOfDeletedNode->right = pDeletedNode->right;
	}
	pMinimalNodeFromRightSubtreeOfDeletedNode->left = pDeletedNode->left;
	if (pDeletedNode != (pBST->root)) {
		if (pParentOfDeletedNode->right == pDeletedNode) {
			pParentOfDeletedNode->right = pMinimalNodeFromRightSubtreeOfDeletedNode;
		} else {
			pParentOfDeletedNode->left = pMinimalNodeFromRightSubtreeOfDeletedNode;
		}
	} else {
		(pBST->root) = pMinimalNodeFromRightSubtreeOfDeletedNode;
	}
}

void deleteBSTNodeFromBST(BST *pBST, BSTptr pNode) {
	BSTptr pParent;
	
	if (pNode != NULL) {
		pBST->size--;
		pParent = getParentOfBSTNode(pBST->root, pNode);
		if (pNode->right == NULL && pNode->left == NULL) {
			case_A(pBST, pNode, pParent);
		} else if (pNode->right == NULL || pNode->left == NULL) {
			case_B(pBST, pNode, pParent);
		} else {
			case_C(pBST, pNode, pParent);
		}
		free(pNode);
	}
}
