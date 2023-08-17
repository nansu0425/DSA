#include <stdio.h>
#include <stdlib.h>
#include "stack_using_linked_list.h"

Stack* CreateStack(void) // 스택 생성
{
    Stack* stack = malloc(sizeof * stack);
    if (stack == NULL) return NULL;

    stack->top = NULL;

    return stack;
}

SNode* CreateNode(SData data, SNode* next) // 노드 생성
{
    SNode* node = malloc(sizeof * node);
    if (node == NULL) return NULL;

    node->data = data;
    node->next = next;

    return node;
}

int IsEmpty(Stack* stack) // 스택이 비었는지 확인
{
    if (stack == NULL) return ERROR;

    return (stack->top == NULL) ? TRUE : FALSE;
}

int Push(Stack* stack, SData data) // 스택에 데이터 한 개를 넣는다
{
    if (stack == NULL) return FALSE;

    SNode* new_node = CreateNode(data, stack->top);
    stack->top = new_node;

    return TRUE;
}

int Pop(Stack* stack, SData* data_ptr) // 스택에서 데이터 한 개를 뺀다
{
    if (IsEmpty(stack) != FALSE) return FALSE;

    SNode* rm_node = stack->top;
    *data_ptr = rm_node->data;
    stack->top = rm_node->next;
    free(rm_node);

    return TRUE;
}

int Peek(Stack* stack, SData* data_ptr) // 스택에 마지막으로 들어간 데이터를 확인
{
    if (IsEmpty(stack) != FALSE) return FALSE;

    *data_ptr = stack->top->data;

    return TRUE;
}

int TraverseStack(Stack* stack) // 스택의 모든 데이터를 순회화며 출력
{
    if (IsEmpty(stack) != FALSE) return FALSE;

    SNode* cur = stack->top;
    printf("top->%c", cur->data->data);

    while (cur->next != NULL)
    {
        cur = cur->next;
        printf("->%c", cur->data->data);
    }
    printf("\n");

    return TRUE;
}