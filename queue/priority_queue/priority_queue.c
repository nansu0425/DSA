#include <stdio.h>
#include <stdlib.h>
#include "binary_heap.h"

typedef HeapStruct* Queue; // 힙을 기반으로 하는 우선순위 큐

Queue CreateQueue(ComparePriority compare_priority, int capacity) // 큐 생성
{
	Queue queue = CreateHeap(compare_priority, capacity);

	return queue;
}

int Enqueue(Queue queue, Data data) // 큐에 데이터 삽입
{
	return Insert(queue, data);
}

int Dequeue(Queue queue, Data* data_ptr) // 큐의 데이터 삭제
{
	return Delete(queue, 1, data_ptr);
}

int Peek(Queue queue, Data* data_ptr) // 우선순위가 가장 높은 데이터 확인
{
	if (queue == NULL || data_ptr == NULL || IsEmpty(queue))
		return FALSE;

	*data_ptr = queue->arr[1];

	return TRUE;
}

int SetPriority(Queue queue, ComparePriority compare_priority) // 우선순위 기준을 변경
{
	if (queue == NULL || compare_priority == NULL)
		return FALSE;

	queue->compare_priority = compare_priority;
	BuildHeap(queue);

	return TRUE;
}

int CompareMax(Data data1, Data data2) // 값이 크면 우선순위가 더 높다
{
	return data1 - data2;
}

int CompareMin(Data data1, Data data2) // 값이 작으면 우선순위가 더 높다
{
	return data2 - data1;
}

int main()
{
	Queue queue = CreateQueue(CompareMax, 10);
	Data arr[] = { 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 };
	Data data;

	while (IsFull(queue) == FALSE)
	{
		Enqueue(queue, arr[queue->num_of_data]);
		Traverse(queue);
		Peek(queue, &data);
		printf("The highest priority data: %d\n", data);
	}
	printf("\n");

	SetPriority(queue, CompareMin);
	printf("Change priority criteria\n");
	Traverse(queue);
	Peek(queue, &data);
	printf("The highest priority data: %d\n\n", data);

	while (IsEmpty(queue) == FALSE)
	{
		Dequeue(queue, &data);
		printf("Return data of dequeue: %d\n", data);
		Traverse(queue);
	}

	return 0;
}

/*
OUTPUT

Heap: 4
The highest priority data: 4
Heap: 4 1
The highest priority data: 4
Heap: 4 1 3
The highest priority data: 4
Heap: 4 2 3 1
The highest priority data: 4
Heap: 16 4 3 1 2
The highest priority data: 16
Heap: 16 4 9 1 2 3
The highest priority data: 16
Heap: 16 4 10 1 2 3 9
The highest priority data: 16
Heap: 16 14 10 4 2 3 9 1
The highest priority data: 16
Heap: 16 14 10 8 2 3 9 1 4
The highest priority data: 16
Heap: 16 14 10 8 7 3 9 1 4 2
The highest priority data: 16

Change priority criteria
Heap: 1 2 3 4 7 10 9 8 14 16
The highest priority data: 1

Return data of dequeue: 1
Heap: 2 4 3 8 7 10 9 16 14
Return data of dequeue: 2
Heap: 3 4 9 8 7 10 14 16
Return data of dequeue: 3
Heap: 4 7 9 8 16 10 14
Return data of dequeue: 4
Heap: 7 8 9 14 16 10
Return data of dequeue: 7
Heap: 8 10 9 14 16
Return data of dequeue: 8
Heap: 9 10 16 14
Return data of dequeue: 9
Heap: 10 14 16
Return data of dequeue: 10
Heap: 14 16
Return data of dequeue: 14
Heap: 16
Return data of dequeue: 16
Heap is empty
*/