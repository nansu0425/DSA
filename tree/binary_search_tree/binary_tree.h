#pragma once

#define TRUE    1
#define FALSE   0
#define ERROR   -1

typedef int Key; // 노드의 키 타입

typedef struct _Node // 노드 구조체 정의
{
    Key key;
    struct _Node* left;
    struct _Node* right;
} Node;

typedef Node* Tree; // 트리는 루트 노드의 포인터

typedef enum { PREORDER, INORDER, POSTORDER } TraversalWay; // 탐색 방법을 정의

typedef int (*ProcessRoot)(Tree tree); // 탐색한 트리의 루트 처리

Tree CreateTree(Key key); // 트리 생성

int InsertLeftSubtree(Node* root, Tree subtree); // 트리에 왼쪽 서브트리 삽입

int InsertRightSubtree(Node* root, Tree subtree); // 트리에 오른쪽 서브트리 삽입

int Traverse(Tree tree, TraversalWay traversal_way, ProcessRoot process_root); // 트리를 순회

int DeleteRoot(Node* root); // 트리의 루트 노드 삭제

int DeleteLeftSubtree(Node* root); // 트리의 왼쪽 서브트리 삭제

int DeleteRightSubtree(Node* root); // 트리의 오른쪽 서브트리 삭제

int PrintRoot(Node* root); // 루트를 출력

int PrintTree(Tree tree); // 트리를 출력