#include <stdio.h>

void CountingSort(int arr[], int len, int divisor) // divisor 값에 따라 정해지는 자릿수 기준으로 계수 정렬
{
    int i;
    int arr_sorted[len + 1], arr_count[10] = { 0 };

    for (i = 0; i < len; i++) // 특정 자릿수 값에 해당하는 원소의 개수를 센다
        arr_count[(arr[i] / divisor) % 10]++;

    for (i = 1; i < 10; i++) // 값에 따른 원소의 삽입 위치를 저장
        arr_count[i] = arr_count[i] + arr_count[i - 1];
        
    for (i = len - 1; i >= 0; i--) // arr_count의 삽입 위치를 참고하여 arr_sorted에 정렬
        arr_sorted[arr_count[(arr[i] / divisor) % 10]--] = arr[i];
    
    for (i = 1; i <= len; i++) // arr_sorted의 원소들을 arr로 복사
        arr[i - 1] = arr_sorted[i];
}

void RadixSort(int arr[], int len, int digit) // 원소들 중 최대 자릿수가 digit인 배열의 기수 정렬
{
    int i, divisor = 1;

    for (i = 0; i < digit; i++) // 최대값의 자릿수만큼 반복
    {
        // 낮은 자릿수부터 계수 정렬
        CountingSort(arr, len, divisor);
        divisor *= 10; 
    }
}

int main()
{
    int arr[] = {329, 25, 1536, 457, 9, 5362, 657, 839, 86, 5368, 436, 71, 720, 355, 6893, 5};
    int len = sizeof arr / sizeof *arr;

    RadixSort(arr, len, 4);

    for (int i = 0; i < len; i++)
        printf("%d ", arr[i]);
    printf("\n");
    
    return 0;
}

/*
OUTPUT

5 9 25 71 86 329 355 436 457 657 720 839 1536 5362 5368 6893
*/