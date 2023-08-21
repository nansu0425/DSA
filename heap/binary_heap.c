#include <stdio.h>
#include <stdlib.h>

#define TRUE    1
#define FALSE   0
#define ERROR   -1

typedef int Data; // 힙의 데이터 타입

typedef enum {MIN, MAX} Property; // 최대 힙 또는 최소 힙 결정

typedef enum {DOWN, UP} Direction; // heapify의 swap 방향 

typedef struct // 힙 구조 정의
{
    Data *arr;
    Property property;
    int capacity;
    int num_of_data;
} HeapStruct;

typedef HeapStruct *Heap; // 힙을 가리키는 포인터

Heap CreateHeap(Property property, int capacity) // 힙 생성
{
    if ((property != MAX && property != MIN) || capacity < 1)
        return NULL;

    Heap heap = malloc(sizeof *heap);
    if (heap == NULL) return NULL;

    heap->arr = malloc((capacity + 1) * sizeof *(heap->arr));
    if (heap->arr == NULL) return NULL;

    heap->property = property;
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

int Heapify(Heap heap, int current, Direction direction) // 노드를 힙의 property에 위배되지 않는 위치로 이동시킨다 
{
    if (heap == NULL || current < 1 || (direction != UP && direction != DOWN))
        return FALSE;
    
    int left, right, parent, target;

    if (direction == UP) // 부모 노드와 비교
    {
        parent = GetParentIdx(current);

        if (parent > 0 && 
            (heap->property == MAX && heap->arr[current] > heap->arr[parent] ||
             heap->property == MIN && heap->arr[current] < heap->arr[parent])
            )
        {
            Swap(&heap->arr[current], &heap->arr[parent]);
            return Heapify(heap, parent, direction);
        }
    }
    else if (direction == DOWN) // 자식 노드와 비교
    {
        left = GetLeftChildIdx(current);
        right = GetRightChildIdx(current);

        if (left <= heap->num_of_data &&
            ((heap->property == MAX && heap->arr[current] < heap->arr[left]) ||
             (heap->property == MIN && heap->arr[current] > heap->arr[left]))
            )
            target = left;
        else target = current;

        if (right <= heap->num_of_data &&
            ((heap->property == MAX && heap->arr[target] < heap->arr[right]) ||
             (heap->property == MIN && heap->arr[target] > heap->arr[right]))
            )
            target = right;

        if (target != current)
        {
            Swap(&heap->arr[current], &heap->arr[target]);
            return Heapify(heap, target, direction);
        }
    }

    return TRUE;
}

int BuildHeap(Heap heap) // 모든 노드가 힙의 property를 만족하도록 이동
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

int Delete(Heap heap, int idx) // 힙에서 노드 삭제
{
    if (heap == NULL || IsEmpty(heap) || idx > heap->num_of_data || idx < 1) return FALSE;

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

int main()
{
    Heap heap = CreateHeap(MAX, 15);
    heap->arr[1] = 4;
    heap->arr[2] = 1;
    heap->arr[3] = 3;
    heap->arr[4] = 2;
    heap->arr[5] = 16;
    heap->arr[6] = 9;
    heap->arr[7] = 10;
    heap->arr[8] = 14;
    heap->arr[9] = 8;
    heap->arr[10] = 7;
    heap->num_of_data = 10;

    BuildHeap(heap);
    Traverse(heap);
    /*
                16
          /            \
         14            10
       /    \        /    \
      8      7      9      3
     / \    /
    2   4  1
    */

    printf("Insert 18\n");    
    Insert(heap, 18);
    Traverse(heap);
    /*
                18
          /            \
         16            10
       /    \        /    \
      8     14      9      3
     / \    / \
    2   4  1   7
    */

    printf("Insert 11\n");   
    Insert(heap, 11);
    Traverse(heap);
    /*
                18
          /            \
         16            11
       /    \        /    \
      8     14      10     3
     / \    / \    /
    2   4  1   7  9
    */

    printf("Delete second node\n");
    Delete(heap, 2);
    Traverse(heap);
    /*
                18
          /            \
         14            11
       /    \        /    \
      8      9      10     3
     / \    / \
    2   4  1   7
    */

    printf("Delete first node\n");
    Delete(heap, 1);
    Traverse(heap);
    /*
                14
          /            \
         9             11
       /    \        /    \
      8      7      10     3
     / \    /
    2   4  1   
    */

    return 0;
}