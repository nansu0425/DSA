#include <stdio.h>
#include <stdlib.h>

#define TRUE    1
#define FALSE   0
#define ERROR   -1

typedef int Data; // 큐의 데이터 타입

typedef struct _Queue // 큐 구조체 정의
{
    Data *arr;
    int front, rear;
    int capacity;
    int size;
} Queue;

Queue *CreateQueue(int capacity) // 큐 생성
{
    Queue *queue = malloc(sizeof *queue);
    if (queue == NULL) return NULL;
    
    queue->arr = malloc(capacity * sizeof *(queue->arr));
    if (queue->arr == NULL)
    {
        free(queue);
        return NULL;
    }

    queue->front = queue->rear = -1;
    queue->capacity = capacity;
    queue->size = 0;

    return queue;
}

int IsEmpty(Queue *queue) // 큐가 비었는지 확인
{
    if (queue == NULL) return ERROR;

    return (queue->front == queue->rear) ? TRUE : FALSE;
}

int IsFull(Queue *queue) // 큐가 가득 찼는지 확인
{
    if (queue == NULL) return ERROR;

    return (queue->rear == queue->capacity - 1) ? TRUE : FALSE; 
}

int Enqueue(Queue *queue, Data data) // rear에 데이터를 넣는다
{
    if (IsFull(queue) != FALSE) return FALSE;

    queue->rear++;
    queue->arr[queue->rear] = data;
    queue->size++;

    return TRUE;
}

int Dequeue(Queue *queue, Data *data_ptr) // front의 데이터를 뺀다
{
    if (IsEmpty(queue) != FALSE) return FALSE;

    queue->front++;
    *data_ptr = queue->arr[queue->front];
    queue->size--;

    return TRUE;
}

int Rear(Queue *queue, Data *data_ptr) // rear의 데이터를 확인
{
    if (IsEmpty(queue) != FALSE) return FALSE;

    *data_ptr = queue->arr[queue->rear];

    return TRUE;
}

int Front(Queue *queue, Data *data_ptr) // front의 데이터 확인
{
    if (IsEmpty(queue) != FALSE) return FALSE;

    *data_ptr = queue->arr[queue->front + 1];

    return TRUE;
}

int Size(Queue *queue) // 큐의 데이터 개수 확인
{
    if (queue == NULL) return ERROR;

    return queue->size;
}

int Traverse(Queue *queue) // 큐의 모든 데이터를 순회하며 출력
{
    if (IsEmpty(queue) != FALSE)
    {
        printf("Queue is empty\n");
        return FALSE;
    }

    printf("Queue: ");
    for (int i = queue->front + 1; i <= queue->rear; i++)
        printf("%d ", queue->arr[i]);
    printf("\n");

    return TRUE;
}

int main()
{
    Queue *queue = CreateQueue(5);
    Data data1, data2;

    for (int i = 0; i < 5; i++)
    {
        Enqueue(queue, i);
        Rear(queue, &data1);
        printf("Enqueue %d, size: %d\n", data1, Size(queue));
    } 
    Traverse(queue);

    while (IsEmpty(queue) == FALSE)
    {
        Front(queue, &data1);
        Dequeue(queue, &data2);
        printf("Front: %d, Dequeue %d\n", data1, data2);
    }
    Traverse(queue);

    if (IsFull(queue) == TRUE)
        printf("Queue is full\n");

    return 0;
}

/*
OUTPUT

Enqueue 0, size: 1
Enqueue 1, size: 2
Enqueue 2, size: 3
Enqueue 3, size: 4
Enqueue 4, size: 5
Queue: 0 1 2 3 4
Front: 0, Dequeue 0
Front: 1, Dequeue 1
Front: 2, Dequeue 2
Front: 3, Dequeue 3
Front: 4, Dequeue 4
Queue is empty
Queue is full
*/