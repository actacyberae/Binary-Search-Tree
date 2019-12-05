#include "./BST.h"

void BSTInsertNode(BST *pBST, int pKey) {
	BSTBinarySearchVacancy(pBST, &pBST->root, pBST->root, pKey);
}

void BSTBinarySearchVacancy(BST *pBST, BSTptr *pRoot, BSTptr pNode, int pKey) {
	while (1) {
		if (pNode == NULL) {
			BSTCreate(pBST, pRoot, pNode, pKey);
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

void BSTCreateNode(BSTptr *pRoot, BSTptr pNode, int pKey) {
	pNode = *pRoot = (BSTptr) malloc(sizeof(BSTnode));
	pNode->key = pKey;
	pNode->left = pNode->right = NULL;
}

void BSTCreate(BST *pBST, BSTptr *pRoot, BSTptr pNode, int pKey) {
	BSTCreateNode(pRoot, pNode, pKey);
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

void freeNode(BSTptr pNode) {
	if (pNode != NULL) {
		freeNode(pNode->left);
		freeNode(pNode->right);
		free(pNode);
	}
}

void freeBST(BST *pBST) {
	freeNode(pBST->root);
}

BSTptr searchNode(BSTptr pNode, int pKey) {
	if (pNode != NULL) {
		if (pKey < pNode->key) {
			return searchNode(pNode->left, pKey);
		} else if (pKey > pNode->key) {
			return searchNode(pNode->right, pKey);
		} else {
			return pNode;
		}
	} else {
		return NULL;
	}
}

BSTptr searchBST(BST *pBST, int pKey) {
	return searchNode(pBST->root, pKey);
}

BSTptr searchMinimalSubBST(BSTptr pNode) {
	if (pNode != NULL) {
		if (pNode->left != NULL) {
			return searchMinimalSubBST(pNode->left);
		} else {
			return pNode;
		}
	} else {
		return NULL;
	}
}

BSTptr searchMaximumSubBST(BSTptr pNode) {
	if (pNode != NULL) {
		if (pNode->right != NULL) {
			return searchMaximumSubBST(pNode->right);
		} else {
			return pNode;
		}
	} else {
		return NULL;
	}
}

BSTptr searchMinimalBST(BST *pBST) {
	return searchMinimalSubBST(pBST->root);
}

BSTptr searchMaximumBST(BST *pBST) {
	return searchMaximumSubBST(pBST->root);
}

BSTptr getParentNode(BSTptr pParent, BSTptr pNode) {
	if (pParent != NULL) {
		if (pParent->right == pNode || pParent->left == pNode) {
			return pParent;
		} else {
			if (pParent->key > pNode->key) {
				return getParentNode(pParent->left, pNode);
			} else if (pParent->key < pNode->key) {
				return getParentNode(pParent->right, pNode);
			} else {
				return NULL;
			}
		}
	} else {
		return NULL;
	}
}

BSTptr getParentNodeFromBST(BST *pBST, int pKey) {
	BSTptr pNode;

	pNode = searchBST(pBST, pKey);
	if (pNode != NULL) {
		return getParentNode(pBST->root, pNode);
	} else {
		return NULL;
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
	
	pMin = searchMinimalSubBST(pNode->right);
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

void deleteNode(BST *pBST, int pKey) {
	BSTptr pNode;
	BSTptr pParent;
	
	pBST->size--;
	pNode = searchBST(pBST, pKey);
	if (pNode != NULL) {
		pParent = getParentNodeFromBST(pBST, pKey);
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