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
} Node;

typedef struct _Queue // 큐의 구조체 정의
{
    Node *front, *rear;
    int size;
} Queue;

Node *CreateNode(Data data, Node *next) // 노드 생성
{
    Node *node = malloc(sizeof *node);
    if (node == NULL) return NULL;

    node->data = data;
    node->next = next;

    return node;
}

Queue *CreateQueue() // 큐 생성
{
    Queue *queue = malloc(sizeof *queue);
    if (queue == NULL) return NULL;

    queue->front = queue->rear = NULL;
    queue->size = 0;

    return queue;
}

int IsEmpty(Queue *queue) // 큐가 비어있는지 확인
{
    if (queue == NULL) return ERROR;

    return (queue->front == NULL) ? TRUE : FALSE;
}

int Enqueue(Queue *queue, Data data) // rear에 데이터를 넣는다
{
    if (queue == NULL) return FALSE;
    
    Node *new_node = CreateNode(data, NULL);
    if (IsEmpty(queue)) 
        queue->front = new_node;
    else
        queue->rear->next = new_node;
    queue->rear = new_node;
    queue->size++;

    return TRUE;
}

int Dequeue(Queue *queue, Data *data_ptr) // front의 데이터를 뺀다
{
    if (IsEmpty(queue)) return FALSE;

    Node *rm_node = queue->front;
    *data_ptr = rm_node->data;
    queue->front = rm_node->next;
    free(rm_node);
    queue->size--;

    return TRUE;
}

int Front(Queue *queue, Data *data_ptr) // front의 데이터를 확인
{
    if (IsEmpty(queue)) return FALSE;

    *data_ptr = queue->front->data;

    return TRUE;
}

int Rear(Queue *queue, Data *data_ptr) // Rear의 데이터를 확인
{
    if (IsEmpty(queue)) return FALSE;

    *data_ptr = queue->rear->data;

    return TRUE;
}

int Size(Queue *queue) // 큐의 데이터 개수 확인
{
    if (queue == NULL) return ERROR;

    return queue->size;
}

int Traverse(Queue *queue) // 큐의 모든 데이터를 순회하며 출력
{
    if (IsEmpty(queue))
    {
        printf("Queue is empty\n");
        return FALSE;
    }

    Node *cur = queue->front;
    printf("Queue: %d", cur->data);
    while (cur->next != NULL)
    {
        cur = cur->next;
        printf("->%d", cur->data);
    }
    printf("\n");

    return TRUE;
}

int main()
{
    Queue *queue = CreateQueue();
    Data data1, data2;

    for (int i = 0; i < 5; i++)
    {
        Enqueue(queue, i);
        Rear(queue, &data1);
        printf("Enqueue %d\tsize: %d\n", data1, Size(queue));
    } 
    Traverse(queue);

    while (IsEmpty(queue) == FALSE)
    {
        Front(queue, &data1);
        Dequeue(queue, &data2);
        printf("Front: %d\tDequeue %d\n", data1, data2);
    }
    Traverse(queue);

    return 0;
}

/*
OUTPUT

Enqueue 0       size: 1
Enqueue 1       size: 2
Enqueue 2       size: 3
Enqueue 3       size: 4
Enqueue 4       size: 5
Queue: 0->1->2->3->4
Front: 0        Dequeue 0
Front: 1        Dequeue 1
Front: 2        Dequeue 2
Front: 3        Dequeue 3
Front: 4        Dequeue 4
Queue is empty
*/