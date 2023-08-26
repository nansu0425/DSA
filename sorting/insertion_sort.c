#include <stdio.h>

void Swap(int* a, int* b) // 두 변수의 값을 교환
{
    int prev_b = *b;
    *b = *a;
    *a = prev_b;
}

void InsertionSort(int arr[], int len) // 오름차순으로 삽입 정렬
{
    int i, j, ins_elem;

    for (i = 1; i < len; i++) // 정렬된 영역이 왼쪽 끝에서 오른쪽으로 하나씩 늘어난다
    {
        ins_elem = arr[i];

        for (j = i - 1; j >= 0; j--) // i번 원소를 삽입할 수 있을 때까지 정렬된 영역의 원소를 뒤로 이동
        {
            if (arr[j] > ins_elem)
                Swap(&arr[j], &arr[j + 1]);
            else break;
        }

        if (j + 1 < i) // 정렬된 영역에 i번 원소를 삽입
            arr[j + 1] = ins_elem;
    }
}

int main()
{
    int arr[] = {5, 0, 7, 1, 6, 8, 3, 2, 9, 4};
    int len = sizeof arr / sizeof *arr;

    InsertionSort(arr, len);

    for (int i = 0; i < len; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}

/*
OUPUT

0 1 2 3 4 5 6 7 8 9
*/