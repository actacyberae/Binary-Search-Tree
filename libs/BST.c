#include "./BST.h"

void insertBSTNodeInBST(BST *pBST, int pKey) {
	getVacancyPlaceForBSTNodeInBST(pBST, &pBST->root, pBST->root, pKey);
}

void getVacancyPlaceForBSTNodeInBST(BST *pBST, BSTptr *pRoot, BSTptr pNode, int pKey) {
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

void createBSTNodeInBST(BSTptr *pRoot, BSTptr pNode, int pKey) {
	pNode = *pRoot = (BSTptr) malloc(sizeof(BSTnode));
	pNode->key = pKey;
	pNode->left = pNode->right = NULL;
}

void createBST(BST *pBST, BSTptr *pRoot, BSTptr pNode, int pKey) {
	createBSTNodeInBST(pRoot, pNode, pKey);
	pBST->size++;
}

void BSTWalk(BST *pBST) {
	BSTInOrderTraversal(pBST->root);
}

void BSTInOrderTraversal(BSTptr pNode) {
	if (pNode != NULL) {
		BSTInOrderTraversal(pNode->left);
		// <- Some process -> //
		BSTInOrderTraversal(pNode->right);
	}
}

void printBST(BST *pBST) {
	printBSTInOrderTraversal(pBST->root);
}

void printBSTInOrderTraversal(BSTptr pNode) {
	if (pNode != NULL) {
		printBSTInOrderTraversal(pNode->left);
		print_line(STDOUT_FILENO, "[%d].\n", pNode->key);
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

void case_A(BST *pBST, BSTptr pNode, BSTptr pParent) {
	if (pParent != NULL) {
		if (pParent->right == pNode) {
			pParent->right = NULL;
		} else {
			pParent->left = NULL;
		}
	} else {
		pBST->root = NULL;
	}
}

void case_B(BST *pBST, BSTptr pNode, BSTptr pParent) {
	if (pParent != NULL) {
		if (pParent->right == pNode) {
			if (pNode->right != NULL) {
				pParent->right = pNode->right;
			} else {
				pParent->right = pNode->left;
			}
		} else {
			if (pNode->right != NULL) {
				pParent->left = pNode->right;
			} else {
				pParent->left = pNode->left;
			}
		}
	} else {
		if (pNode->right != NULL) {
			pBST->root = pNode->right;
		} else {
			pBST->root = pNode->left;
		}
	}
}

void case_C(BST *pBST, BSTptr pNode, BSTptr pParent) {
	BSTptr pMin;
	
	pMin = getMinimalBSTNodeInSubBST(pNode->right);
	if (pParent != NULL) {
		if (pParent->right == pNode) {
			pParent->right = pMin;
		} else {
			pParent->left = pMin;
		}
	} else {
		pBST->root = pMin;
	}
	
	if (pNode->right != pMin) {
		pMin->right = pNode->right;
	} else {
		pMin->right = pMin->right;
	}
	pMin->left = pNode->left;
}

void deleteBSTNodeFromBSTByKey(BST *pBST, int pKey) {
	BSTptr pNode;
	BSTptr pParent;
	
	pNode = getBSTNodeInBSTByKey(pBST, pKey);
	if (pNode != NULL) {
		pBST->size--;
		pParent = getParentOfBSTNodeByKey(pBST, pKey);
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
