#include <stdio.h>
#include <stdlib.h>

#define TRUE    1
#define FALSE   0
#define ERROR   -1

typedef int Data; // 스택의 데이터 타입

typedef struct _Stack // 스택 구조체 정의
{
    Data *array;
    int top;
    int capacity;
} Stack;

Stack *CreateStack(int capacity) // 스택 생성
{
    Stack *stack = malloc(sizeof *stack);
    if (stack == NULL) return NULL;

    stack->array = malloc(capacity * sizeof *(stack->array));
    if (stack->array == NULL) return NULL;

    stack->top = -1;
    stack->capacity = capacity;

    return stack;
}

int IsEmpty(Stack *stack) // 스택이 비었는지 확인
{
    if (stack == NULL) return ERROR;
    
    return (stack->top == -1) ? TRUE : FALSE;
}

int IsFull(Stack *stack) // 스택이 가득 찼는지 확인
{
    if (stack == NULL) return ERROR;

    return (stack->top == stack->capacity - 1) ? TRUE : FALSE;
}

int Push(Stack *stack, Data data) // 스택에 데이터 한 개가 들어간다
{
    if (IsFull(stack)) return FALSE;

    stack->top++;
    stack->array[stack->top] = data;

    return TRUE;
}

int Pop(Stack *stack, Data *data_ptr) // 스택에서 데이터 한 개를 뺀다
{
    if (IsEmpty(stack)) return FALSE;

    *data_ptr = stack->array[stack->top];
    stack->top--;

    return TRUE;
}

int Peek(Stack *stack, Data *data_ptr) // 스택에 마지막으로 들어간 데이터 확인
{
    if (IsEmpty(stack)) return FALSE;

    *data_ptr = stack->array[stack->top];

    return TRUE;
}

int Traverse(Stack *stack) // 스택의 모든 데이터를 순회하며 출력
{
    if (IsEmpty(stack)) return FALSE;

    for (int i = 0; i < stack->top + 1; i++)
        printf("%d ", stack->array[i]);
    printf("\n");
     
    return TRUE;
}

int main()
{
    Stack *stack = CreateStack(10); // 데이터 10개를 저장할 수 있는 스택 생성
    Data data;

    for (int i = 0; i < 10; i++) // 데이터 10개를 넣는다
    {
        Push(stack, i);
        Peek(stack, &data);
        printf("Push %d\n", data);
    }           
    Traverse(stack);

    if (Push(stack, 10) == FALSE) // 용량을 초과하여 데이터를 넣을 수 없다
        printf("Push Failed\n");
    Traverse(stack);

    for (int i = 0; i < 10; i++) // 데이터 10개를 뺀다
    {
        Pop(stack, &data);
        printf("Pop %d\n", data);
    }           

     if (Pop(stack, &data) == FALSE) // 비어있는 스택에서 데이터를 뺄 수 없다
        printf("Pop Failed\n");

    if (Traverse(stack) == FALSE) // 출력할 데이터가 없다
        printf("Stack is Empty");
}