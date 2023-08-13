#pragma once

#define TRUE    1
#define FALSE   0
#define ERROR   -1

typedef int Data; // 스택의 데이터 타입

typedef struct _Node // 노드 구조체 정의
{
    Data data;
    struct _Node* next;
} Node;

typedef struct _Stack // 스택 구조체 정의
{
    Node* top;
} Stack;

Stack* CreateStack(void); // 스택 생성

Node* CreateNode(Data data, Node* next); // 노드 생성

int IsEmpty(Stack* stack); // 스택이 비었는지 확인

int Push(Stack* stack, Data data); // 스택에 데이터 한 개를 넣는다

int Pop(Stack* stack, Data* data_ptr); // 스택에서 데이터 한 개를 뺀다

int Peek(Stack* stack, Data* data_ptr); // 스택에 마지막으로 들어간 데이터를 확인

int Traverse(Stack* stack); // 스택의 모든 데이터를 순회화며 출력

void Test(); // 구현한 스택을 테스트