#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef int Data; // 노드의 데이터 타입 정의

typedef struct _Node // 노드 구조체 정의
{
    Data data;
    struct _Node *next;
} Node;

typedef Node *Tail; // tail의 타입 정의

Node *CreateNode(Data data, Node *next) // 노드 생성
{
    Node *node = malloc(sizeof *node);
    
    if (node == NULL) // 메모리 할당 실패
        return NULL;
    
    node->data = data;
    node->next = (next == NULL) ? node : next;

    return node;
}

Node *GetNode(Tail tail, int nth) // n번째 노드 접근
{
    if (nth < 0 || tail == NULL) // 정의되지 않은 위치 또는 비어있는 리스트
        return NULL;

    if (nth == 0) // 0번 노드는 마지막 노드로 정의
        return tail;
    
    Node *cur = tail->next;

    while (nth > 1) // 목표 노드까지 cur을 이동
    {   
        cur = cur->next;
        nth--;
    }

    return cur;
}

int Traverse(Tail tail) // 전체 노드 순회하며 출력
{
    if (tail == NULL) // 비어있는 리스트
    {
        printf("The linked list is empty\n");
        return FALSE;
    }

    Node *first = tail->next;
    printf("%d", first->data);
    Node *cur = first->next;

    while (cur != first) // 마지막 노드까지 출력
    {
        printf("->%d", cur->data);
        cur = cur->next;
    }
    printf("\n");

    return TRUE;
}

int Insert(Tail *tail_ptr, Data data, int nth) // n번째 위치에 노드 삽입
{   
    if (tail_ptr == NULL || nth < 0) // 참조 중인 tail이 없거나 정의되지 않은 위치
        return FALSE;

    if (*tail_ptr == NULL) // 비어있는 리스트
        *tail_ptr = CreateNode(data, NULL);
    else
    {
        Node *prev = GetNode(*tail_ptr, (nth == 0) ? 0 : nth - 1);
        prev->next = CreateNode(data, prev->next);
        if (nth == 0) *tail_ptr = prev->next; // 0번에 삽입된 노드는 마지막 노드가 된다
    }

    return TRUE;
}

int Delete(Tail *tail_ptr, int nth) // n번째 노드 삭제
{
    if (tail_ptr == NULL || *tail_ptr == NULL || nth < 1) // 참조 중인 tail이 없거나 비어있는 리스트, 정의되지 않은 위치
        return FALSE;

    Node *prev = GetNode(*tail_ptr, nth - 1);
    Node *cur = prev->next;

    if (cur == prev) // 노드 한 개만 존재
        *tail_ptr = NULL;
    else
    {
        if (*tail_ptr == cur) // 삭제하려는 노드가 마지막 노드
            *tail_ptr = prev;

        prev->next = cur->next;
    }
    free(cur);
    
    return TRUE;
}