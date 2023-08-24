#pragma once

#define TRUE    1
#define FALSE   0
#define ERROR   -1

typedef int Data; // 힙의 데이터 타입

typedef int (*ComparePriority)(Data data1, Data data2); // data1의 우선순위가 더 높으면 양수, data2의 우선순위가 더 높으면 음수 반환

typedef enum { DOWN, UP } Direction; // heapify의 swap 방향 

typedef struct // 힙 구조 정의
{
    Data* arr;
    ComparePriority compare_priority;
    int capacity;
    int num_of_data;
} HeapStruct;

typedef HeapStruct* Heap; // 힙을 가리키는 포인터

Heap CreateHeap(ComparePriority compare_priority, int capacity); // 힙 생성

int GetParentIdx(int idx); // 부모 노드의 인덱스

int GetLeftChildIdx(int idx); // 왼쪽 자식 노드의 인덱스

int GetRightChildIdx(int idx); // 오른쪽 자식 노드의 인덱스

int Swap(Data* data1_ptr, Data* data2_ptr); // 데이터 두 개의 값을 서로 바꾼다

int Heapify(Heap heap, int current, Direction direction); // 노드를 힙의 우선순위에 위배되지 않는 위치로 이동시킨다

int BuildHeap(Heap heap); // 모든 노드가 힙의 우선순위를 만족하도록 이동

int IsFull(Heap heap); // 힙이 가득 찼는지 확인

int IsEmpty(Heap heap); // 힙이 비었는지 확인

int Insert(Heap heap, Data data); // 힙에 노드 삽입

int Delete(Heap heap, int idx, Data* data_ptr); // 힙에서 노드 삭제

int Traverse(Heap heap); // 모든 노드를 순회하며 출력