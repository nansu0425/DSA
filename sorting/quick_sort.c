#include <stdio.h>

void Swap(int* a, int* b) // 두 변수의 값을 교환
{
    int prev_b = *b;
    *b = *a;
    *a = prev_b;
}

int Partition(int arr[], int first, int last) // arr[pivot]보다 작은 부분, 큰 부분으로 나눈 후 pivot 반환
{
    int pivot = last; // 마지막 원소를 pivot으로 잡는다
    int i = first - 1; // arr[pivot]보다 작은 부분의 가장 높은 인덱스
    int j;

    for (j = first; j < pivot; j++)
    {
        if (arr[j] <= arr[pivot]) // arr[pivot]보다 작거나 같은 원소인 경우
            Swap(&arr[++i], &arr[j]); // i + 1번 원소와 교환
    }
    Swap(&arr[++i], &arr[pivot]); // pivot 원소를 정렬 조건에 맞는 위치로 이동 

    return i; // 정렬된 pivot 원소의 인덱스 반환
}

void QuickSort(int arr[], int first, int last) // 오름차순으로 퀵 정렬
{
    int pivot;

    if (first < last) 
    {
        pivot = Partition(arr, first, last); // pivot 위치 계산
        QuickSort(arr, first, pivot - 1); // pivot 원소보다 작은 부분 정렬
        QuickSort(arr, pivot + 1, last); // pivot 원소보다 큰 부분 정렬
    }
}

void PrintArray(int arr[], int len) // 배열 출력
{
    for (int i = 0; i < len; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main()
{
    int arr[] = {2, 8, 7, 1, 3, 5, 6, 4};
    int len = sizeof arr / sizeof *arr;

    QuickSort(arr, 0, len - 1);
    PrintArray(arr, len);

    return 0;
}

/*
OUTPUT

1 2 3 4 5 6 7 8
*/