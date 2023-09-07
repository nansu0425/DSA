#include <stdio.h>
#include <stdlib.h>
#include "binary_search_tree.h"

int GetHeight(Tree tree) // 트리의 높이를 반환
{
	if (tree == NULL) 
		return -1;

	if (tree->left == NULL && tree->right == NULL)
		return 0;

	int height_left = GetHeight(tree->left);
	int height_right = GetHeight(tree->right);

	if (height_left < height_right) // 더 높은 서브트리의 높이에 1을 더하여 반환
		return height_right + 1;
	else
		return height_left + 1;
}

int GetBalanceFactor(Tree tree) // 균형 인자를 반환
{
	return GetHeight(tree->left) - GetHeight(tree->right);
}

Node* RotateLL(Tree tree) // LL 회전을 하고 바뀐 루트 노드 반환
{
	if (tree == NULL)
		return NULL;

	Node* parent = tree;
	Node* child = tree->left;

	parent->left = child->right;
	child->right = parent;

	return child;
}

Node* RotateRR(Tree tree) // RR 회전을 하고 바뀐 루트 노드 반환
{
	if (tree == NULL)
		return NULL;

	Node* parent = tree;
	Node* child = tree->right;

	parent->right = child->left;
	child->left = parent;

	return child;
}

Node* RotateLR(Tree tree) // LR 회전을 하고 바뀐 루트 노드 반환
{
	if (tree == NULL)
		return NULL;

	Node* parent = tree;
	Node* child = tree->left;

	parent->left = RotateRR(child);
	
	return RotateLL(parent);
}

Node* RotateRL(Tree tree) // RL 회전을 하고 바뀐 루트 노드 반환
{
	if (tree == NULL)
		return NULL;

	Node* parent = tree;
	Node* child = tree->right;

	parent->right = RotateLL(child);

	return RotateRR(parent);
}

int BalanceTree(Tree* ptr_tree) // 트리의 균형 인자 절댓값을 1 이하로 만든다
{
	if (ptr_tree == NULL || *ptr_tree == NULL)
		return FALSE;

	int balance_factor = GetBalanceFactor(*ptr_tree);

	if (balance_factor > 1) // 왼쪽 서브트리의 높이가 오른쪽 서브트리보다 2 이상 큰 경우
	{
		if (GetBalanceFactor((*ptr_tree)->left) < 0)
			*ptr_tree = RotateLR(*ptr_tree);
		else
			*ptr_tree = RotateLL(*ptr_tree);
	}
	else if (balance_factor < -1) // 오른쪽 서브트리의 높이가 왼쪽 서브트리보다 2 이상 큰 경우
	{
		if (GetBalanceFactor((*ptr_tree)->right) > 0)
			*ptr_tree = RotateRL(*ptr_tree);
		else
			*ptr_tree = RotateRR(*ptr_tree);
	}

	return TRUE;
}

int InsertAndBalance(Tree* ptr_tree, Key key) // 삽입 후 균형을 맞춘다
{
	if (ptr_tree == NULL)
		return FALSE;

	if (*ptr_tree == NULL) // 노드가 없는 경우
	{
		*ptr_tree = CreateTree(key); // 트리 생성
		return TRUE;
	}
		
	if (key < (*ptr_tree)->key) // 삽입하려는 key가 더 작을 때 왼쪽 서브트리 탐색
		InsertAndBalance(&((*ptr_tree)->left), key);
	else if (key > (*ptr_tree)->key) // 삽입하려는 key가 더 클 때 오른쪽 서브트리 탐색
		InsertAndBalance(&((*ptr_tree)->right), key);
	else
		return FALSE;

	BalanceTree(ptr_tree); // 트리의 균형을 맞춘다
	
	return TRUE;
}

int DeleteAndBalance(Tree* ptr_tree, Key key) // 삭제 후 균형을 맞춘다
{
	if (ptr_tree == NULL || *ptr_tree == NULL)
		return FALSE;

	if (key < (*ptr_tree)->key) // 삭제하려는 key가 더 작을 때 왼쪽 서브트리 탐색
		DeleteAndBalance(&((*ptr_tree)->left), key);
	else if (key > (*ptr_tree)->key) // 삭제하려는 key가 더 클 때 오른쪽 서브트리 탐색
		DeleteAndBalance(&((*ptr_tree)->right), key);
	else // key를 찾았을 때
	{
		if ((*ptr_tree)->left == NULL || (*ptr_tree)->right == NULL)
		{
			Node* parent = *ptr_tree;
			Node* del = (parent->left) ? parent->left : parent->right;

			if (del == NULL) // 단말 노드인 경우
			{
				del = parent;
				*ptr_tree = NULL;
			}
			else // 자식 노드가 1개인 경우
				*parent = *del;

			free(del); 
		}
		else // 자식 노드가 2개인 경우
		{
			Node* min = (*ptr_tree)->right;

			while (min->left) // 오른쪽 서브트리의 최소 key 탐색
				min = min->left;

			(*ptr_tree)->key = min->key;

			DeleteAndBalance(&((*ptr_tree)->right), min->key);
		}
	}

	BalanceTree(ptr_tree); // 트리의 균형을 맞춘다

	return TRUE;
}

int main()
{
	Tree tree = NULL;
	Key* arr_key;
	Key key;
	int len, i, num = 0;

	printf("Enter the number of keys: ");
	scanf_s("%d", &len);

	arr_key = malloc(len * sizeof(*arr_key));
	if (arr_key == NULL)
		exit(-1);

	printf("Enter the keys: ");
	for (i = 0; i < len; i++)
	{
		scanf_s("%d", &key);
		if (InsertAndBalance(&tree, key))
			arr_key[num++] = key;
	}
	
	printf("\nCurrent tree\n");
	PrintTree(tree);
	printf("\n");

	for (i = 0; i < num; i++)
	{
		if (DeleteAndBalance(&tree, arr_key[i]))
		{
			printf("%d is deleted\n", arr_key[i]);
			PrintTree(tree);
			printf("\n");
		}
	}

	return 0;
}

/*
OUTPUT

Enter the number of keys: 7
Enter the keys: 0 1 2 3 4 5 6

Current tree
Preorder traversal: 3 1 0 2 5 4 6
Inorder traversal: 0 1 2 3 4 5 6
Postorder traversal: 0 2 1 4 6 5 3

0 is deleted
Preorder traversal: 3 1 2 5 4 6
Inorder traversal: 1 2 3 4 5 6
Postorder traversal: 2 1 4 6 5 3

1 is deleted
Preorder traversal: 3 2 5 4 6
Inorder traversal: 2 3 4 5 6
Postorder traversal: 2 4 6 5 3

2 is deleted
Preorder traversal: 5 3 4 6
Inorder traversal: 3 4 5 6
Postorder traversal: 4 3 6 5

3 is deleted
Preorder traversal: 5 4 6
Inorder traversal: 4 5 6
Postorder traversal: 4 6 5

4 is deleted
Preorder traversal: 5 6
Inorder traversal: 5 6
Postorder traversal: 6 5

5 is deleted
Preorder traversal: 6
Inorder traversal: 6
Postorder traversal: 6

6 is deleted
Tree is empty
*/