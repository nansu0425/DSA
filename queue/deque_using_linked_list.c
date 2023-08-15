#include <stdio.h>
#include <stdlib.h>

#define TRUE    1
#define FALSE   0
#define ERROR   -1

typedef int Data; // 큐의 데이터 타입

typedef struct _Node // 노드의 구조체 정의
{
    Data data;
    struct _Node *next;
    struct _Node *prev;
} Node;

typedef struct _Deque // 큐의 구조체 정의
{
    Node *front, *rear;
    int size;
} Deque;

Node *CreateNode(Data data, Node *next, Node *prev) // 노드 생성
{
    Node *node = malloc(sizeof *node);
    if (node == NULL) return NULL;

    node->data = data;
    node->next = next;
    node->prev = prev;

    return node;
}

Deque *CreateDeque() // 덱 생성
{
    Deque *deque = malloc(sizeof *deque);
    if (deque == NULL) return NULL;

    deque->front = deque->rear = NULL;
    deque->size = 0;

    return deque;
}

int IsEmpty(Deque *deque) // 덱이 비었는지 확인
{
    if (deque == NULL) return ERROR;

    return (deque->front == NULL || deque->rear == NULL) ? TRUE : FALSE;
}

int InsertFront(Deque *deque, Data data) // front에 데이터를 추가
{
    if (deque == NULL) return FALSE;

    Node *new_node = CreateNode(data, deque->front, NULL);
    if (new_node == NULL) return FALSE;

    if (IsEmpty(deque))
        deque->rear = new_node;
    else
        deque->front->prev = new_node;
    deque->front = new_node;
    deque->size++;

    return TRUE;
}

int DeleteFront(Deque *deque, Data *data_ptr) // front의 데이터를 삭제
{
    if (IsEmpty(deque)) return FALSE;

    Node *rm_node = deque->front;
    *data_ptr = rm_node->data;
    deque->front = rm_node->next;
    if (deque->front != NULL)
        deque->front->prev = NULL;

    free(rm_node);
    deque->size--;

    return FALSE;
}

int InsertRear(Deque *deque, Data data) // rear에 데이터를 추가
{
    if (deque == NULL) return FALSE;

    Node *new_node = CreateNode(data, NULL, deque->rear);
    if (new_node == NULL) return FALSE;

    if (IsEmpty(deque))
        deque->front = new_node;
    else
        deque->rear->next = new_node;
    deque->rear = new_node;
    deque->size++;

    return TRUE;
}

int DeleteRear(Deque *deque, Data *data_ptr) // rear의 데이터를 삭제
{
    if (IsEmpty(deque)) return FALSE;

    Node *rm_node = deque->rear;
    *data_ptr = rm_node->data;
    deque->rear = rm_node->prev;
    if (deque->rear != NULL) 
        deque->rear->next = NULL;

    free(rm_node);
    deque->size--;

    return TRUE;
}

int Front(Deque *deque, Data *data_ptr) // front의 데이터 확인
{
    if (IsEmpty(deque)) return FALSE;

    *data_ptr = deque->front->data;

    return TRUE;
}

int Rear(Deque *deque, Data *data_ptr) // rear의 데이터 확인
{
    if (IsEmpty(deque)) return FALSE;

    *data_ptr = deque->rear->data;

    return TRUE;
}

int Size(Deque *deque) // 덱의 데이터 개수 확인
{
    if (deque == NULL) return ERROR;

    return deque->size;
}

int Traverse(Deque *deque) // 덱의 모든 데이터를 순회하며 출력
{
    if (IsEmpty(deque)) 
    {
        printf("Deque is empty\n");
        return FALSE;
    }
    
    Node *cur = deque->front;
    printf("Deque: %d", cur->data);
    while(cur->next != NULL)
    {
        cur = cur->next;
        printf("->%d", cur->data);
    }
    printf("\n");

    return TRUE;
}

int main()
{
    Deque *deque = CreateDeque();
    Data data1, data2;
    int i;

    for (i = 0; i < 5; i++)
    {
        printf("Insert %d on both sides\t", i);
        InsertFront(deque, i);
        InsertRear(deque, i);
        Front(deque, &data1);
        Rear(deque, &data2);
        printf("Front: %d, Rear: %d, Size: %d\n", data1, data2, Size(deque));
    }
    Traverse(deque);

    while (IsEmpty(deque) == FALSE)
    {
        printf("Delete both sides\t");
        DeleteFront(deque, &data1);
        DeleteRear(deque, &data2);
        Traverse(deque);
    }
    
    return 0;
}

/*
OUTPUT

Insert 0 on both sides  Front: 0, Rear: 0, Size: 2
Insert 1 on both sides  Front: 1, Rear: 1, Size: 4
Insert 2 on both sides  Front: 2, Rear: 2, Size: 6
Insert 3 on both sides  Front: 3, Rear: 3, Size: 8
Insert 4 on both sides  Front: 4, Rear: 4, Size: 10
Deque: 4->3->2->1->0->0->1->2->3->4
Delete both sides       Deque: 3->2->1->0->0->1->2->3
Delete both sides       Deque: 2->1->0->0->1->2
Delete both sides       Deque: 1->0->0->1
Delete both sides       Deque: 0->0
Delete both sides       Deque is empty
*/