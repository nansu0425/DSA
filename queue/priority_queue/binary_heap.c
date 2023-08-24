#include <stdio.h>
#include <stdlib.h>
#include "binary_heap.h"

Heap CreateHeap(ComparePriority compare_priority, int capacity) // 힙 생성
{
    if (compare_priority == NULL || capacity < 1)
        return NULL;

    Heap heap = malloc(sizeof *heap);
    if (heap == NULL) return NULL;

    heap->arr = malloc((capacity + 1) * sizeof *(heap->arr));
    if (heap->arr == NULL) return NULL;

    heap->compare_priority = compare_priority;
    heap->capacity = capacity;
    heap->num_of_data = 0;

    return heap;
}

int GetParentIdx(int idx) // 부모 노드의 인덱스
{
    return idx >> 1;
}

int GetLeftChildIdx(int idx) // 왼쪽 자식 노드의 인덱스
{
    return idx << 1;
}

int GetRightChildIdx(int idx) // 오른쪽 자식 노드의 인덱스
{
    return (idx << 1) + 1;
}

int Swap(Data *data1_ptr, Data *data2_ptr) // 데이터 두 개의 값을 서로 바꾼다
{
    if (data1_ptr == NULL || data2_ptr == NULL)
        return FALSE;

    Data tmp = *data2_ptr;
    *data2_ptr = *data1_ptr;
    *data1_ptr = tmp;

    return TRUE;
}

int Heapify(Heap heap, int current, Direction direction) // 노드를 힙의 우선순위에 위배되지 않는 위치로 이동시킨다 
{
    if (heap == NULL || current < 1 || (direction != UP && direction != DOWN))
        return FALSE;
    
    int left, right, parent, target;

    if (direction == UP) // 부모 노드와 비교
    {
        parent = GetParentIdx(current);

        if (parent > 0 && heap->compare_priority(heap->arr[current], heap->arr[parent]) > 0)
        { // 부모 노드보다 현재 노드의 우선순위가 더 높은 경우
            Swap(&heap->arr[current], &heap->arr[parent]);
            return Heapify(heap, parent, direction);
        }
    }
    else if (direction == DOWN) // 자식 노드와 비교
    {
        left = GetLeftChildIdx(current);
        right = GetRightChildIdx(current);

        if (left <= heap->num_of_data && heap->compare_priority(heap->arr[left], heap->arr[current]) > 0) 
            target = left; // 왼쪽 자식 노드의 우선순위가 더 높은 경우
        else target = current;

        if (right <= heap->num_of_data && heap->compare_priority(heap->arr[right] , heap->arr[target]) > 0)
            target = right; // 오른쪽 자식 노드의 우선순위가 더 높은 경우

        if (target != current) // 현재 노드보다 자식 노드의 우선순위가 더 높은 경우
        {
            Swap(&heap->arr[current], &heap->arr[target]);
            return Heapify(heap, target, direction);
        }
    }

    return TRUE;
}

int BuildHeap(Heap heap) // 모든 노드가 힙의 우선순위를 만족하도록 이동
{
    if (heap == NULL) return FALSE;

    int i;

    for (i = heap->capacity / 2; i > 0; i--)
        Heapify(heap, i, DOWN);

    return TRUE;
}

int IsFull(Heap heap) // 힙이 가득 찼는지 확인
{
    if (heap == NULL) return ERROR;

    return (heap->num_of_data == heap->capacity) ? TRUE : FALSE;
}

int IsEmpty(Heap heap) // 힙이 비었는지 확인
{
    if (heap == NULL) return ERROR;

    return (heap->num_of_data == 0) ? TRUE : FALSE;
}

int Insert(Heap heap, Data data) // 힙에 노드 삽입
{
    if (heap == NULL || IsFull(heap)) return FALSE;

    heap->arr[++heap->num_of_data] = data;
    Heapify(heap, heap->num_of_data, UP);

    return TRUE;
}

int Delete(Heap heap, int idx, Data* data_ptr) // 힙에서 노드 삭제
{
    if (heap == NULL || IsEmpty(heap) || idx > heap->num_of_data || idx < 1 || data_ptr == NULL) return FALSE;

    *data_ptr = heap->arr[idx];
    heap->arr[idx] = heap->arr[heap->num_of_data--];
    Heapify(heap, idx, DOWN);

    return TRUE;
}

int Traverse(Heap heap) // 모든 노드를 순회하며 출력
{
    if (heap == NULL) return ERROR;

    if (IsEmpty(heap) == TRUE)
    {
        printf("Heap is empty\n");
        return FALSE;
    }

    printf("Heap: ");
    for (int i = 1; i <= heap->num_of_data; i++)
        printf("%d ", heap->arr[i]);
    printf("\n");

    return TRUE;
}