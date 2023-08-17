#pragma once

#include "binary_tree.h"

#define TRUE    1
#define FALSE   0
#define ERROR   -1

typedef Tree SData; // 스택의 데이터 타입

typedef struct _SNode // 노드 구조체 정의
{
    SData data;
    struct _SNode* next;
} SNode;

typedef struct _Stack // 스택 구조체 정의
{
    SNode* top;
} Stack;

Stack* CreateStack(void); // 스택 생성

SNode* CreateNode(SData data, SNode* next); // 노드 생성

int IsEmpty(Stack* stack); // 스택이 비었는지 확인

int Push(Stack* stack, SData data); // 스택에 데이터 한 개를 넣는다

int Pop(Stack* stack, SData* data_ptr); // 스택에서 데이터 한 개를 뺀다

int Peek(Stack* stack, SData* data_ptr); // 스택에 마지막으로 들어간 데이터를 확인

int TraverseStack(Stack* stack); // 스택의 모든 데이터를 순회화며 출력