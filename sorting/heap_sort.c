#include <stdio.h>
#include <stdlib.h>

#define ROOT    1

void Swap(int* a, int* b) // 두 변수의 값을 교환
{
    int prev_b = *b;
    *b = *a;
    *a = prev_b;
}

void MaxHeapify(int arr[], int last, int cur) // cur 원소를 최대힙 조건에 맞는 위치로 이동
{
    int left = cur * 2;
    int right = cur * 2 + 1;
    int max;

    if (left <= last && arr[left] > arr[cur]) // 왼쪽 자식 노드가 부모 노드보다 큰 경우
        max = left;
    else max = cur;

    if (right <= last && arr[right] > arr[max]) // 오른쪽 자식 노드가 가장 큰 경우
        max = right;
    
    if (max != cur) // 자식 노드가 부모 노드보다 크면 서로 교환
    {    
        Swap(&arr[max], &arr[cur]);
        MaxHeapify(arr, last, max);
    }
}

void BuildMaxHeap(int arr[], int last) // arr의 모든 원소를 힙 조건에 맞게 정렬
{
    int i;

    for (i = last / 2; i > 0; i--)
        MaxHeapify(arr, last, i);
}

void HeapSort(int arr[], int last) // 오름차순으로 힙 정렬
{
    int i = last;

    BuildMaxHeap(arr, last); // arr를 힙으로 만든다

    while (i > ROOT) // 최대힙의 루트를 i번 원소와 교환하여 큰 값부터 정렬
    {
        Swap(&arr[ROOT], &arr[i--]);
        MaxHeapify(arr, i, ROOT);
    }
}

int* CreateArray(int num_of_elem) // 배열을 생성하고 원소를 입력
{
    int *arr = malloc((num_of_elem + 1) * sizeof *arr);

    printf("Input elements: ");
    for (int i = ROOT; i <= num_of_elem; i++)
        scanf("%d", &arr[i]);

    return arr;
}

void PrintArray(int arr[], int num_of_elem) // 배열의 모든 원소 출력
{
    int i;

    for (i = ROOT; i <= num_of_elem; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main()
{
    int* arr;
    int num_of_elem;

    printf("Input the number of elements: ");
    scanf("%d", &num_of_elem);

    arr = CreateArray(num_of_elem);
    HeapSort(arr, num_of_elem);

    printf("Result of heapsort: ");
    PrintArray(arr, num_of_elem);

    return 0;
}

/*
OUTPUT

Input the number of elements: 10
Input elements: 4 1 3 2 16 9 10 14 8 7
Result of heapsort: 1 2 3 4 7 8 9 10 14 16
*/