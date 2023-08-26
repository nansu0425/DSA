#include <stdio.h>
#include <stdbool.h>

void Swap(int* a, int* b) // 두 변수의 값을 교환
{
    int tmp = *b;
    *b = *a;
    *a = tmp;
}

void SelectionSort(int arr[], int len) // 오름차순으로 선택 정렬
{
    int i, j, min_idx;

    for (i = 0; i < len - 1; i++) // 정렬된 영역이 배열의 가장 왼쪽부터 오른쪽으로 하나씩 늘어난다
    {
        min_idx = i;

        for (j = i + 1; j < len; j++) // 정렬되지 않은 영역의 최솟값을 선택 
        {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }

        if (min_idx > i) // 정렬되지 않은 영역의 최솟값을 정렬된 영역 오른쪽 끝에 추가
            Swap(&arr[min_idx], &arr[i]);
    }
}

int main()
{
    int arr[] = {0, 9, 2, 5, 1, 6, 3, 4, 7, 8};
    int len = sizeof arr / sizeof *arr;

    SelectionSort(arr, len);

    for (int i = 0; i < len; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}

/*
OUTPUT

0 1 2 3 4 5 6 7 8 9
*/