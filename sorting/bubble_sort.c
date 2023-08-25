#include <stdio.h>
#include <stdbool.h>

void Swap(int* a, int* b) // 두 변수의 값 교환
{
    int tmp = *b;
    *b = *a;
    *a = tmp;
}

void BubbleSort(int arr[], int len) // arr를 오름차순으로 버블 정렬
{
    int i, j;
    bool swaped = false;

    for (i = 1; i < len; i++) // 배열의 오른쪽 끝부터 정렬된 영역이 왼족 방향으로 하나씩 늘어난다
    {
        
        for (j = 0; j < len - i; j++) // 정렬되지 않은 영역에서 가장 큰 원소를 len - i로 옮긴다
        {
            if (arr[j] > arr[j + 1])
            {
                Swap(&arr[j], &arr[j + 1]);
                swaped = true;
            }
        }

        if (!swaped) // swap이 한번도 일어나지 않은 것은 정렬된 상태를 의미하므로 정렬 종료
            break;
    }
}

int main()
{
    int arr[] = {9, 3, 2, 6, 0, 4 ,1, 7, 5, 8};
    BubbleSort(arr, sizeof arr / sizeof *arr);

    for (int i = 0; i < 10; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}

/*
OUTPUT

0 1 2 3 4 5 6 7 8 9
*/