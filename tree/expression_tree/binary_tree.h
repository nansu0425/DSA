#pragma once

#define TRUE    1
#define FALSE   0
#define ERROR   -1

typedef int TData; // 트리의 데이터 타입

typedef struct _Node // 노드 구조체 정의
{
    TData data;
    struct _Node* left;
    struct _Node* right;
} TNode;

typedef TNode* Tree; // 트리는 루트 노드의 포인터

typedef enum { PREORDER, INORDER, POSTORDER } TraversalWay; // 탐색 방법을 정의

typedef int (*ProcessRoot)(Tree tree); // 탐색한 트리의 루트 처리

Tree CreateTree(TData data); // 트리 생성

int InsertLeftSubtree(TNode* root, Tree subtree); // 루트 노드의 왼쪽 서브트리 삽입

int InsertRightSubtree(TNode* root, Tree subtree); // 루트 노드의 오른쪽 서브트리 삽입

int TraverseTree(Tree tree, TraversalWay traversal_way, ProcessRoot process_root); // 트리를 순회

int DeleteRoot(TNode* root); // 트리의 루트 노드 삭제

int DeleteLeftSubtree(TNode* root); // 트리의 왼쪽 서브트리 삭제

int DeleteRightSubtree(TNode* root); // 트리의 오른쪽 서브트리 삭제

int PrintRoot(TNode* root); // 루트를 출력

int PrintTree(Tree tree); // 트리를 출력