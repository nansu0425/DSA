#include <stdio.h>
#include <stdlib.h>

#define TRUE    1
#define FALSE   0

typedef int Data; // 정렬할 배열의 데이터 타입

typedef struct // 원형 큐로 버킷을 구현
{
    int* queue; 
    int len;
    int front, rear;
} BucketStruct;

typedef BucketStruct* Bucket; // 버킷 구조체를 가리키는 포인터

Bucket CreateBucket(int size) // 버킷 생성
{
    Bucket bucket = malloc(sizeof *bucket);
    if (bucket == NULL) return NULL;
    
    bucket->queue = malloc((size + 1) * sizeof *(bucket->queue)); 
    bucket->len = size + 1;
    bucket->front = bucket->rear = 0;

    return bucket;
}

void DeleteBucket(Bucket bucket) // 버킷 삭제
{
    free(bucket->queue);
    free(bucket);
}

int IsFull(Bucket bucket) // 버킷에 원소가 가득 찼는지 확인
{
    return bucket->front == (bucket->rear + 1) % bucket->len ? TRUE : FALSE;
}

int IsEmpty(Bucket bucket) // 버킷이 비었는지 확인
{
    return bucket->front == bucket->rear ? TRUE : FALSE;
}

int Enqueue(Bucket bucket, Data data) // 버킷의 rear를 이동시켜 데이터를 넣는다
{
    if (IsFull(bucket)) return FALSE;
    
    bucket->rear = (bucket->rear + 1) % bucket->len;
    bucket->queue[bucket->rear] = data;

    return TRUE;
}

int Dequeue(Bucket bucket, Data* ptr_data) // 버킷의 front를 이동시켜 데이터를 뺀다
{
    if (IsEmpty(bucket)) return FALSE;

    bucket->front = (bucket->front + 1) % bucket->len;
    *ptr_data = bucket->queue[bucket->front];

    return TRUE;
}

void PrintArray(Data arr[], int len) // 배열의 모든 원소를 출력
{
    for (int i = 0; i < len; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void RadixSort(Data arr_data[], int len, int digit_max) // 원소의 최대 자릿수가 digit_max인 배열을 기수 정렬
{
    Bucket arr_bucket[10];
    int idx_bucket, idx_data, idx_digit;
    int divisor = 1;
    Data data;

    for (idx_bucket = 0; idx_bucket < 10; idx_bucket++) // 10개의 버킷 생성
        arr_bucket[idx_bucket] = CreateBucket(len);

    for (idx_digit = 1; idx_digit <= digit_max; idx_digit++) // 첫 번째 자릿수부터 정렬하여 최대 자릿수까지 정렬
    {
        for (idx_data = 0; idx_data < len; idx_data++) // 배열의 모든 원소를 특정 자릿수 기준으로 분류하여 버킷에 넣는다
        {
            idx_bucket = (arr_data[idx_data] / divisor) % 10;
            Enqueue(arr_bucket[idx_bucket], arr_data[idx_data]);
        }

        for (idx_data = idx_bucket = 0; idx_bucket < 10; idx_bucket++) // 0~9번 버킷 순으로 데이터를 꺼내 배열에 정렬
        {
            while (Dequeue(arr_bucket[idx_bucket], &data))
                arr_data[idx_data++] = data;
        }

        divisor *= 10; // 정렬 기준이 되는 자릿수 하나 증가

        printf("sort on %d-digit: ", idx_digit);
        PrintArray(arr_data, len);
    }

    for (idx_bucket = 0; idx_bucket < 10; idx_bucket++) // 모든 버킷을 삭제
        DeleteBucket(arr_bucket[idx_bucket]);
}

int main()
{
    Data arr[] = {329, 25, 1536, 457, 9, 5362, 657, 839, 86, 5368, 436, 71, 720, 355, 6893, 5};
    int len = sizeof arr / sizeof *arr;

    RadixSort(arr, len, 4);
    return 0;
}

/*
OUTPUT

sort on 1-digit : 720 71 5362 6893 25 355 5 1536 86 436 457 657 5368 329 9 839 
sort on 2-digit : 5 9 720 25 329 1536 436 839 355 457 657 5362 5368 71 86 6893
sort on 3-digit : 5 9 25 71 86 329 355 5362 5368 436 457 1536 657 720 839 6893
sort on 4-digit : 5 9 25 71 86 329 355 436 457 657 720 839 1536 5362 5368 6893 
*/