#include <stdio.h>
#include <stdlib.h>

#define TRUE    1
#define FALSE   0
#define ERROR   -1

typedef int Data;

typedef struct _Node
{
    Data data;
    struct _Node *next;
} Node;

typedef struct _Stack
{
    Node *top;
} Stack;

Stack *CreateStack(void) // 스택 생성
{
    Stack *stack = malloc(sizeof *stack);
    if (stack == NULL) return NULL;

    stack->top = NULL;

    return stack;
}

Node *CreateNode(Data data, Node *next) // 노드 생성
{
    Node *node = malloc(sizeof *node);
    if (node == NULL) return NULL;

    node->data = data;
    node->next = next;

    return node;
}

int IsEmpty(Stack *stack) // 스택이 비었는지 확인
{
    if (stack == NULL) return ERROR;

    return (stack->top == NULL) ? TRUE : FALSE;
}

int Push(Stack *stack, Data data) // 스택에 데이터 한 개를 넣는다
{
    if (stack == NULL) return FALSE;

    Node *new_node = CreateNode(data, stack->top);
    stack->top = new_node;

    return TRUE;
}

int Pop(Stack *stack, Data *data_ptr) // 스택에서 데이터 한 개를 뺀다
{
    if (IsEmpty(stack) != FALSE) return FALSE;

    Node *rm_node = stack->top;
    *data_ptr = rm_node->data;
    stack->top = rm_node->next;
    free(rm_node);

    return TRUE;
}

int Peek(Stack *stack, Data *data_ptr) // 스택에 마지막으로 들어간 데이터를 확인
{
    if (IsEmpty(stack) != FALSE) return FALSE;

    *data_ptr = stack->top->data;

    return TRUE;
}

int Traverse(Stack *stack) // 스택의 모든 데이터를 순회화며 출력
{
    if (IsEmpty(stack) != FALSE) return FALSE;

    Node *cur = stack->top;
    printf("top->%d", cur->data);

    while (cur->next != NULL)
    {
        cur = cur->next;
        printf("->%d", cur->data);
    }
    printf("\n");

    return TRUE;
}

void Test()
{
    Stack *stack = CreateStack(); // 스택 생성
    Data data;

    for (int i = 0; i < 5; i++) // 스택에 데이터 다섯 개를 넣는다
    {
        Push(stack, i);
        Peek(stack, &data);
        printf("Push %d\n", data);
    }
    Traverse(stack);

    while (IsEmpty(stack) == FALSE) // 스택의 모든 데이터를 뺀다
    {
        Pop(stack, &data);
        printf("Pop %d\n", data);
    }
    
    if (Traverse(stack) == FALSE) // 순회할 데이터가 없다
        printf("Stack is empty");
    
    free(stack);
}