#include <stdio.h>
#include <stdlib.h>
#include "binary_search_tree.h"

Node* Search(Tree tree, Key key, Node** ptr_parent) // 키에 해당하는 노드 탐색 후 반환
{
	if (tree == NULL) return NULL; // 트리가 비었으면 탐색 종료

	Node* cur = tree; // 현재 가리키는 노드
	Node* parent = NULL; // 현재 노드의 부모 노드

	while (cur != NULL && cur->key != key) // 탐색 중인 키가 나올 때까지 한 레벨씩 내려간다
	{
		parent = cur;

		if (key < cur->key) // 탐색 중인 키가 현재 노드의 키보다 작으면
			cur = cur->left; // 현재 노드는 왼쪽 자식 노드가 된다
		else cur = cur->right; // 현재 노드 키보다 탐색 중인 키가 크면 오른쪽 자식 노드로 이동
	}

	if (ptr_parent != NULL)
		*ptr_parent = parent;

	return cur;
}

int InsertKey(Tree* ptr_tree, Key key) // 이진 탐색 트리에 키 삽입
{
	Node* parent = NULL; // 삽입할 위치의 부모 노드
	
	if (Search(*ptr_tree, key, &parent)) // 키를 탐색하며 부모 노드 설정 
		return FALSE; // 트리에 삽입할 키가 이미 존재하면 삽입 중단
	else
	{
		if (parent == NULL) // 트리에 노드에 존재하지 않으면 루트 노드로 삽입
			*ptr_tree = CreateTree(key);
		else
		{
			if (key < parent->key) // 삽입할 키가 부모 노드보다 작으면 왼쪽 자식 노드로 삽입
				parent->left = CreateTree(key);
			else parent->right = CreateTree(key); // 삽입할 키가 부모 노드보다 크면 오른쪽 자식 노드로 삽입
		}
	}

	return TRUE;
}

int TransplantSubtree(Tree* ptr_tree, Node* ptr_target_parent, Tree subtr_target, Tree subtr_new) // 특정 서브트리를 새로운 서브트리로 교체한다
{
	if (*ptr_tree == subtr_target) // 교체하려는 서브트리가 트리의 루트인 경우 
		*ptr_tree = subtr_new; // 루트를 새로운 트리로 교체
	else
	{
		if (ptr_target_parent->left == subtr_target) // 교체하려는 서브트리가 왼쪽
			ptr_target_parent->left = subtr_new;
		else if (ptr_target_parent->right == subtr_target) // 교체하려는 서브트리가 오른쪽
			ptr_target_parent->right = subtr_new;
		else
			return FALSE;
	}

	return TRUE;
}

int DeleteKey(Tree* ptr_tree, Key key) // 이진 탐색 트리에서 키 삭제
{
	Node* cur, * par; // cur는 삭제할 노드, par는 cur의 부모 노드

	if (!(cur = Search(*ptr_tree, key, &par))) // 삭제 노드 탐색
		return FALSE;
	
	if (cur->left == NULL) // 삭제 노드에 왼쪽 자식 노드가 없는 경우
		TransplantSubtree(ptr_tree, par, cur, cur->right);
	else if (cur->right == NULL) // 삭제 노드에 왼쪽 자식 노드만 있는 경우
		TransplantSubtree(ptr_tree, par, cur, cur->left);
	else // 삭제 노드에 양쪽 자식 노드 모두 있는 경우
	{
		Node* min_cur = cur->right;
		Node* min_par = cur;

		while (min_cur->left != NULL) // cur의 오른쪽 서브트리에서 최소 키를 갖는 노드를 찾는다
		{
			min_par = min_cur;
			min_cur = min_cur->left;
		}

		if (min_cur != cur->right) // 최소 키 노드가 cur의 오른쪽 자식 노드보다 밑에 있는 경우
		{
			TransplantSubtree(ptr_tree, min_par, min_cur, min_cur->right); // 최소 키 노드를 최소 키 노드의 오른쪽 자식 노드로 교체
			min_cur->right = cur->right; // 최소 키 노드의 오른쪽에 삭제할 노드의 오른쪽 서브트리를 연결
		}
		TransplantSubtree(ptr_tree, par, cur, min_cur); // 삭제할 노드를 최소 키 노드로 교체
		min_cur->left = cur->left; // 최소 키 노드의 왼쪽에 삭제 노드의 왼쪽 서브트리를 연결
	}
	DeleteRoot(cur); // 삭제 노드의 메모리 할당 해제

	return TRUE;
}

void PrintBinarySearchTree(Tree tree) // 이진 탐색 트리를 출력
{
	if (tree == NULL) // 트리가 빈 경우
	{
		printf("The binary search tree is empty\n");
		return;
	}

	printf("Current binary search tree: ");
	Traverse(tree, INORDER, PrintRoot); // 중위 순회하며 키 출력
	printf("\n");
}