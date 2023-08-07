#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef int Data; // 노드의 데이터 타입

typedef struct _Node // 노드 구조
{
    Data data;
    struct _Node *next;
    struct _Node *prev;
} Node;

typedef Node *Head; // head의 타입

Node *CreateNode(Data data, Node *next, Node *prev) // 노드 생성
{
    Node *node = malloc(sizeof *node);

    if (node == NULL) // 메모리 할당 실패
        return NULL;

    node->data = data;
    node->next = next;
    node->prev = prev;

    return node;
}

Node *Access(Head head, int nth) // n번째 노드 접근
{
    if (head == NULL || nth < 1) // 노드가 없거나 정의되지 않은 위치
        return NULL;

    for (int i = 1; i < nth; i++) // n번째 노드까지 head 이동
    {
        if (head->next == NULL)
            return NULL;
        head = head->next;
    }
    
    return head;
}

int Insert(Head *head_ptr, int nth, Data data) // n번째 위치에 노드 삽입
{
    if (head_ptr == NULL || nth < 1) // head의 포인터가 없거나 정의되지 않은 위치
        return FALSE;

    if (nth == 1) // 첫 번째 노드 앞에 삽입
    {
        *head_ptr = CreateNode(data, *head_ptr, NULL);
        if ((*head_ptr)->next != NULL) (*head_ptr)->next->prev = *head_ptr;
    }
    else // 첫 번째 노드 이후에 삽입
    {
        Node *nth_prev = Access(*head_ptr, nth - 1);
        if (nth_prev == NULL) return FALSE;
        nth_prev->next = CreateNode(data, nth_prev->next, nth_prev);
        if (nth_prev->next->next != NULL) nth_prev->next->next->prev = nth_prev->next;
    }

    return TRUE;
}

int Delete(Head *head_ptr, int nth) // n번째 노드 삭제
{
    if (head_ptr == NULL || *head_ptr == NULL || nth < 1) // 노드를 삭제할 수 없는 경우
        return FALSE;
    
    if (nth == 1) // 첫 번째 노드 삭제
    {
        if ((*head_ptr)->next == NULL) // 노드가 한 개
        {
            free(*head_ptr);
            *head_ptr = NULL;
        }
        else // 노드가 두 개 이상
        {
            *head_ptr = (*head_ptr)->next;
            free((*head_ptr)->prev);
        }
    }
    else // 첫 번째 이후 노드 삭제
    {
        Node *nth_prev = Access(*head_ptr, nth - 1);
        if (nth_prev == NULL || nth_prev->next == NULL) return FALSE;
        if (nth_prev->next->next == NULL) // 마지막 노드 삭제
        {
            free(nth_prev->next);
            nth_prev->next = NULL;
        }
        else // 첫 번째와 마지막 노드 사이 중간 노드
        {
            nth_prev->next = nth_prev->next->next;
            free(nth_prev->next->prev);
            nth_prev->next->prev = nth_prev;
        }
    }

    return TRUE;
}

int Traverse(Head head) // 모든 노드를 순회하며 출력
{
    if (head == NULL) // 노드가 없는 경우
        return FALSE;
    
    printf("%d", head->data);
    while (head->next != NULL) // 마지막 노드까지 출력
    {
        head = head->next;
        printf("->%d", head->data);
    }
    printf("\n");

    return TRUE;
}