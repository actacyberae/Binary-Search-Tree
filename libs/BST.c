#include "./BST.h"

/*
* Простая функция распечатки информации об узле pNode: ключе и цвете вер
* шины. Если узел имеет левого и/или правого потомка, то информация такж
* е выводится и для них. Формат информации следующий:
* [КЛП|КВ|КПП], где
* КЛП - ключ левого потомка
* КПП - ключ правого потомка
* КВ  - ключ вершины
* Если потомок у вершины отсутствует, то вместо информации о потомке, пи
* шется слово NULL.
*/
void node_info(BSTptr pNode) {
	print_line(STDOUT_FILENO, "[");
	if (pNode != NULL) {
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
	} else {
		print_line(STDOUT_FILENO, "NULL");
	}
	print_line(STDOUT_FILENO, "]\n");
}

/*
* Рекурсивная функция распечатки содержимого поддерева с корнем pRoot в 
* порядке симметричного обхода дерева. Пусть корень поддерева обозначает
* ся буквой A, а его левый и правый потомки B и C соответственно.
*      |
*      A
*     / \
*    /   \
*   B     C
* Печать:
* > B A C
*/
static void info_in_order_traversal(BSTptr pRoot) {
	if (pRoot != NULL) {
		info_in_order_traversal(pRoot->left);
		node_info(pRoot);
		info_in_order_traversal(pRoot->right);
	}
}

/*
* Обобщенная функция печати дерева pBST. В качестве входящего параметра 
* рекурсивной функции печати выступает корень дерева pBST. Т. о., дерево
* обходится в порядке симметричного обхода и последовательно распечатыва
* ется вся информация об узлах.
*/
void tree_info(BST *pBST) {
	info_in_order_traversal(pBST->root);
}

/*
* Функция возвращает родителя вершины pNode дерева pBST. В случае, если 
* берется корень дерева pBST, то возвращается само корневое значение. Пу
* сть корень поддерева обозначается буквой A, а его левый и правый потом
* ки B и C соответственно. Данные сохраняются в pParent по значению.
*      |
*      A
*     / \
*    /   \
*   B     C
* Тогда вызов функции get_parent_of_node для узла C вернет вершину A.
*/
static int get_parent_of_node(BST *pBST, BSTptr pNode, BSTptr *pParent) {
	int pKey;
	
	if (pBST == NULL) {
		return ER_EMPTYTREE;
	}
	if (pNode == NULL) {
		return ER_EMPTYNODE;
	}
	pKey = pNode->key;
	*pParent = pBST->root;
	while (*pParent != NULL) {
		if ((*pParent)->right == pNode || (*pParent)->left == pNode) {
			return TRUE;
		}
		if ((*pParent)->key > pKey) {
			*pParent = (*pParent)->left;
		} else if ((*pParent)->key < pKey) {
			*pParent = (*pParent)->right;
		} else {
			break;
		}
	}
	return FALSE;
}

static void Get_parent_of_node(BST *pBST, BSTptr pNode, BSTptr *pParent) {
	int RETURN;
	
	RETURN = get_parent_of_node(pBST, pNode, pParent);
	switch (RETURN) {
		case ER_EMPTYTREE:
			err_msg("get_parent_of_node: ER_EMPTYTREE\n");
			exit(EXIT_FAILURE);
		case ER_EMPTYNODE:
			err_msg("get_parent_of_node: ER_EMPTYNODE\n");
			exit(EXIT_FAILURE);
	}
}

/*
* Функция проверки на то, что узел pNode является левым, либо правым пот
* омком в узла pParent. Если pParent не является родителем pNode, то фун
* кция возвращает отрицательное значение.
*/
static int is_node_a_left_child(BSTptr pNode, BSTptr pParent) {
	if (pNode == NULL || pParent == NULL) {
		return ER_EMPTYNODE;
	}
	if (pParent->left == pNode) {
		return TRUE;
	} else if (pParent->right == pNode) {
		return FALSE;
	} else {
		return ER_UNKNWPRNT;
	} 
}

static int Is_node_a_left_child(BSTptr pNode, BSTptr pParent) {
	int RETURN;
	
	RETURN = is_node_a_left_child(pNode, pParent);
	switch (RETURN) {
		case ER_EMPTYNODE:
			err_msg("is_node_a_left_child: ER_EMPTYNODE\n");
			exit(EXIT_FAILURE);
		case ER_UNKNWPRNT:
			err_msg("is_node_a_left_child: ER_UNKNWPRNT\n");
			exit(EXIT_FAILURE);
		default:
			return RETURN;
	}
}

/*
* Функция возвращает брата вершины pNode дерева pBST. В случае, если бер
* ется корень дерева pBST, то возвращается само корневое значение. Пусть
* корень поддерева обозначается буквой A, а его левый и правый потомки -
* B и C соответственно. Данные сохраняются в pNodeBrother по значению.  
*      |
*      A
*     / \
*    /   \
*   B     C
* Тогда вызов функции get_sibling_node для узла C вернет вершину B.
*/
static int get_sibling_node(BST *pBST, BSTptr pNode, BSTptr *pNodeBrother) {
	BSTptr pParent;
	
	if (pBST == NULL) {
		return ER_EMPTYTREE;
	}
	if (pNode == NULL) {
		return ER_EMPTYNODE;
	}
	if (pBST->root != pNode) {
		Get_parent_of_node(pBST, pNode, &pParent);
		if (Is_node_a_left_child(pNode, pParent) == TRUE) {
			*pNodeBrother = pParent->right;
		} else {
			*pNodeBrother = pParent->left;
		}
	} else {
		*pNodeBrother = NULL;
	}
	return TRUE;
}

static void Get_sibling_node(BST *pBST, BSTptr pNode, BSTptr *pNodeBrother) {
	int RETURN;
	
	RETURN = get_sibling_node(pBST, pNode, pNodeBrother);
	switch (RETURN) {
		case ER_EMPTYTREE:
			err_msg("get_sibling_node: ER_EMPTYTREE\n");
			exit(EXIT_FAILURE);
		case ER_EMPTYNODE:
			err_msg("get_sibling_node: ER_EMPTYNODE\n");
			exit(EXIT_FAILURE);
	}
}

/*
* Функция возвращает вершину с минимальным ключом в поддереве с корнем в
* A. Архитектура дерева такова, что минимальная вершина всегда будет леж
* ать слева от корня. Для дерева приведенного ниже, такой вершиной будет
* узел B.
*      |
*      A
*     / \
*    /   \
*   B     C
*/
static int get_minimal_node(BSTptr pRoot, BSTptr *pMinimalNode) {
	if (pRoot == NULL) {
		return ER_EMPTYNODE;
	}
	*pMinimalNode = pRoot;
	while (*pMinimalNode != NULL) {
		if ((*pMinimalNode)->left == NULL) {
			return TRUE;
		}
		*pMinimalNode = (*pMinimalNode)->left;
	}
	return ER_EMPTYNODE;
}

static void Get_minimal_node(BSTptr pRoot, BSTptr *pNodeBrother) {
	int RETURN;
	
	RETURN = get_minimal_node(pRoot, pNodeBrother);
	switch (RETURN) {
		case ER_EMPTYNODE:
			err_msg("get_sibling_node: ER_EMPTYNODE\n");
			exit(EXIT_FAILURE);
	}
}

/*
* 
*/
static int get_node(BST *pBST, int pKey, BSTptr *pNode) {
	if (pBST == NULL) {
		return ER_EMPTYTREE;
	}
	*pNode = pBST->root;
	while (*pNode != NULL) {
		if ((*pNode)->key > pKey) {
			*pNode = (*pNode)->left;
		} else if ((*pNode)->key < pKey) {
			*pNode = (*pNode)->right;
		} else if ((*pNode)->key == pKey) {
			return TRUE;
		} else {
			break;
		}
	}
	return ER_EMPTYNODE;
}

void Get_node(BST *pBST, int pKey, BSTptr *pNode) {
	int RETURN;
	
	RETURN = get_node(pBST, pKey, pNode);
	switch (RETURN) {
		case ER_EMPTYTREE:
			err_msg("get_node: ER_EMPTYTREE\n");
			exit(EXIT_FAILURE);
		case ER_EMPTYNODE:
			err_msg("get_node: ER_EMPTYNODE\n");
			*pNode == NULL;
	}
}

/*
* Заменяет поддерево с корнем в узле pNode поддеревом с корнем в узле   
* pNewNode. Родителю узла pNode устанавливается новый левый или правый п
* отомок. Если содержимое дерева заменяется полностью, то корень pBST пр
* инимает новое значение корневого узла pNewNode.                       
*/
static int transplant(BST *pBST, BSTptr pNode, BSTptr pNewNode) {
	BSTptr pParent;
	
	if (pBST == NULL) {
		return ER_EMPTYTREE;
	}
	if (pNode == NULL) {
		return ER_EMPTYNODE;
	}
	if (pBST->root != pNode) {
		Get_parent_of_node(pBST, pNode, &pParent);
		if (Is_node_a_left_child(pNode, pParent) == TRUE) {
			pParent->left = pNewNode;
		} else {
			pParent->right = pNewNode;
		}
	} else {
		pBST->root = pNewNode;
	}
	return TRUE;
}

static void Transplant(BST *pBST, BSTptr pNode, BSTptr pNewNode) {
	int RETURN;
	
	RETURN = transplant(pBST, pNode, pNewNode);
	switch (RETURN) {
		case ER_EMPTYTREE:
			err_msg("transplant: ER_EMPTYTREE\n");
			exit(EXIT_FAILURE);
		case ER_EMPTYNODE:
			err_msg("transplant: ER_EMPTYNODE\n");
			exit(EXIT_FAILURE);
	}
}

/*
* 
*/
static void declare_a_new_node(BST *pBST, BSTptr *pRoot, BSTptr *pNode, int pKey) {
	*pNode = *pRoot = (BSTptr) Malloc(sizeof(BSTnode));
	(*pNode)->key = pKey;
	(*pNode)->left = (*pNode)->right = NULL;
	pBST->size++;
}

/*
* 
*/
static void insert_node(BST *pBST, BSTptr *pRoot, BSTptr pNode, int pKey) {
	BSTptr pParent;
	
	if (pNode == NULL) {
		declare_a_new_node(pBST, pRoot, &pNode, pKey);
	} else {
		while (TRUE) {
			if (pKey < pNode->key) {
				if (pNode->left == NULL) {
					pParent = pNode;
					declare_a_new_node(pBST, &pNode->left, &pNode, pKey);
					break;
				} else {
					pRoot = &pNode->left;
					pNode = pNode->left;
				}
			} else {
				if (pNode->right == NULL) {
					pParent = pNode;
					declare_a_new_node(pBST, &pNode->right, &pNode, pKey);
					break;
				} else {
					pRoot = &pNode->right;
					pNode = pNode->right;
				}
			}
		}
	}
}

/*
 * 
 * */
void Insert_node(BST *pBST, int pKey) {
	insert_node(pBST, &pBST->root, pBST->root, pKey);
}

/*
* Рекурсивная функция free_tree помещает выделенную память под узел дере
* ва в список повторно используемых областей. Указатель pNode может быть
* равным NULL и проверка, используемая внутри функции указателя, использ
* уется для  последовательное перемещения по поддереву с корнем в pRoot 
* в порядке левого обхода.
*/
static void free_tree(BSTptr pRoot) {
	if (pRoot != NULL) {
		free_tree(pRoot->left);
		free_tree(pRoot->right);
		free(pRoot);
	}
}

/*
* Для очистки всего дерева pBST используется функция Free_tree, которая 
* задействует рекурсивную функцию free_tree, в качестве параметра которо
* й передает корень дерева pBST->root.
*/
void Free_tree(BST *pBST) {
	free_tree(pBST->root);
}

/*
* Случай, когда удаляется лист дерева.
*/
static void case_A(BST *pBST, BSTptr *pDeletedNode) {
	Transplant(pBST, *pDeletedNode, NULL);
}

/*
* Случай, когда удаляется вершина дерева с одним потомком.
*/
static void case_B(BST *pBST, BSTptr *pDeletedNode) {
	BSTptr pNewNode;
	
	if ((*pDeletedNode)->left != NULL) {
		pNewNode = (*pDeletedNode)->left;
	} else {
		pNewNode = (*pDeletedNode)->right;
	}
	Transplant(pBST, *pDeletedNode, pNewNode);
}

/*
* Случай, когда удаляется вершина дерева с двумя потомками.
*/
static void case_C(BST *pBST, BSTptr *pDeletedNode) {
	BSTptr pMinimalNodeFromRightSubtreeOfDeletedNode;
	BSTptr pParentOfMinimalNodeFromRightSubtreeOfDeletedNode;
	
	Get_minimal_node((*pDeletedNode)->right, &pMinimalNodeFromRightSubtreeOfDeletedNode);
	Get_parent_of_node(pBST, pMinimalNodeFromRightSubtreeOfDeletedNode, &pParentOfMinimalNodeFromRightSubtreeOfDeletedNode);
	
	if (pParentOfMinimalNodeFromRightSubtreeOfDeletedNode != *pDeletedNode) {
		pParentOfMinimalNodeFromRightSubtreeOfDeletedNode->left = pMinimalNodeFromRightSubtreeOfDeletedNode->right;
	}
	if (pMinimalNodeFromRightSubtreeOfDeletedNode != (*pDeletedNode)->right) {
		pMinimalNodeFromRightSubtreeOfDeletedNode->right = (*pDeletedNode)->right;
	}
	pMinimalNodeFromRightSubtreeOfDeletedNode->left = (*pDeletedNode)->left;
	Transplant(pBST, *pDeletedNode, pMinimalNodeFromRightSubtreeOfDeletedNode);
}

static int free_node(BST *pBST, BSTptr pNode) {
	if (pBST == NULL) {
		return ER_EMPTYTREE;
	}
	if (pNode == NULL) {
		return ER_EMPTYNODE;
	}
	pBST->size--;
	if (pNode->right == NULL && pNode->left == NULL) {
		case_A(pBST, &pNode);
	} else if (pNode->right == NULL || pNode->left == NULL) {
		case_B(pBST, &pNode);
	} else {
		case_C(pBST, &pNode);
	}
	free(pNode);
	return TRUE;
}

void Free_node(BST *pBST, BSTptr pNode) {
	int RETURN;
	
	RETURN = free_node(pBST, pNode);
	switch (RETURN) {
		case ER_EMPTYTREE:
			err_msg("free_node: ER_EMPTYTREE\n");
			exit(EXIT_FAILURE);
		case ER_EMPTYNODE:
			err_msg("free_node: ER_EMPTYNODE\n");
	}
}
