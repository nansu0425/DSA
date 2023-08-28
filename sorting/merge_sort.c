#include <stdio.h>

void Merge(int arr[], int first, int mid, int last) // 정렬된 왼쪽 부분과 오른쪽 부분을 병합
{
    int len_left = mid - first + 1;
    int len_right = last - mid;
    int arr_left[len_left], arr_right[len_right];

    int l, r;

    // 정렬된 왼쪽 절반과 오른쪽 절반을 arr_left, arr_right에 복사
    for (l = 0; l < len_left; l++)
        arr_left[l] = arr[first + l];
    for (r = 0; r < len_right; r++)
        arr_right[r] = arr[mid + 1 + r];

    l = r = 0;
    int i = first;
    
    // arr_left, arr_right의 원소를 값이 작은 것부터 arr에 복사
    while (l < len_left && r < len_right) 
    {
        if (arr_left[l] < arr_right[r])
            arr[i++] = arr_left[l++];
        else
            arr[i++] = arr_right[r++];
    }

    // 복사하지 못한 나머지 원소를 모두 arr에 복사
    while (l < len_left)
        arr[i++] = arr_left[l++];
    while (r < len_right)
        arr[i++] = arr_right[r++];
}

void MergeSort(int arr[], int first, int last) // 오름차순으로 병합 정렬
{
    int mid;

    if (first < last) // 배열의 원소가 두 개 이상일 때
    {
        mid = (first + last) / 2; // 범위를 반으로 나눈다

        MergeSort(arr, first, mid); // 왼쪽 절반을 정렬
        MergeSort(arr, mid + 1, last); // 오른쪽 절반을 정렬
        Merge(arr, first, mid, last); // 정렬된 두 부분을 병합
    }
}

void PrintArray(int arr[], int first, int last) // 배열 출력
{
    for (int i = first; i <= last; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main()
{
    int arr[] = {12, 3, 7, 9, 14, 6, 11, 2};
    int len = sizeof arr / sizeof *arr;
    
    MergeSort(arr, 0, len - 1);
    PrintArray(arr, 0, len - 1);

    return 0;
}

/*
OUTPUT

2 3 6 7 9 11 12 14
*/