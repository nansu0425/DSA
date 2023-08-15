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

    queue->front = queue->rear = 0;
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

    return ((queue->rear + 1) % queue->capacity == queue->front) ? TRUE : FALSE;
}

int Enqueue(Queue *queue, Data data) // rear에 데이터를 넣는다
{
    if (IsFull(queue)) return FALSE;

    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->arr[queue->rear] = data;
    queue->size++;

    return TRUE;
}

int Dequeue(Queue *queue, Data *data_ptr) // front의 데이터를 뺀다
{
    if (IsEmpty(queue)) return FALSE;

    queue->front = (queue->front + 1) % queue->capacity;
    *data_ptr = queue->arr[queue->front];
    queue->size--;

    return TRUE;
}

int Rear(Queue *queue, Data *data_ptr) // rear의 데이터를 확인
{
    if (IsEmpty(queue)) return FALSE;

    *data_ptr = queue->arr[queue->rear];

    return TRUE;
}

int Front(Queue *queue, Data *data_ptr) // front의 데이터를 확인
{
    if (IsEmpty(queue)) return FALSE;

    *data_ptr = queue->arr[(queue->front + 1) % queue->capacity];

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

    printf("Queue: ");

    int i = (queue->front + 1) % queue->capacity;
    while (i != (queue->rear + 1) % queue->capacity)
    {
        printf("%d ", queue->arr[i]);
        i = (i + 1) % queue->capacity;
    }
    printf("\n");

    return TRUE;
}

int main()
{
    Queue *queue = CreateQueue(5);
    Data data1, data2;
    int i;

    for (i = 0; i < 5; i++)
    {
        printf("Enqueue %d ", i);
        if (Enqueue(queue, i))
        {
            Rear(queue, &data1);
            printf("success!\trear: %d size: %d\n", data1, Size(queue));
        }
        else
        {
            Rear(queue, &data1);
            printf("failure..\trear: %d size: %d\n", data1, Size(queue));
        }
    } 
    Traverse(queue);

    while (IsEmpty(queue) == FALSE)
    {
        Front(queue, &data1);
        if (Dequeue(queue, &data2))
            printf("Front: %d\tDequeue %d success!\n", data1, data2);
    }
    Traverse(queue);

    for (i = 'A'; i < 'A'+3; i++)
    {
        printf("Enqueue %c ", i);
        if (Enqueue(queue, i))
        {
            Rear(queue, &data1);
            printf("success!\trear: %c size: %d\n", data1, Size(queue));
        }
    }

    return 0;
}

/*
OUTPUT

Enqueue 0 success!      rear: 0 size: 1
Enqueue 1 success!      rear: 1 size: 2
Enqueue 2 success!      rear: 2 size: 3
Enqueue 3 success!      rear: 3 size: 4
Enqueue 4 failure..     rear: 3 size: 4
Queue: 0 1 2 3
Front: 0        Dequeue 0 success!
Front: 1        Dequeue 1 success!
Front: 2        Dequeue 2 success!
Front: 3        Dequeue 3 success!
Queue is empty
Enqueue A success!      rear: A size: 1
Enqueue B success!      rear: B size: 2
Enqueue C success!      rear: C size: 3
*/