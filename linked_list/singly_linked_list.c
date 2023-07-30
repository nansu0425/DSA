#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef int Data; // 노드의 데이터 타입

typedef struct _Node // 노드 구조체 정의
{
    Data data;
    struct _Node *next;
} Node;

typedef Node *Head; // head의 타입 정의

Node *CreateNode(Data data, Node *next) // 노드 생성
{
    Node *node = malloc(sizeof *node);

    if (node == NULL) // 메모리 할당 실패
        return NULL;

    node->data = data;
    node->next = next;
    
    return node;
}

Node *GetNthNode(Head head, int nth) // n번째 노드 접근
{
    if (nth < 1 || head == NULL) // 정의되지 않은 위치 또는 비어있는 리스트
        return NULL;
    
    Node *cur = head;

    while (nth > 1) // n번 노드까지 cur을 이동
    {   
        if ((cur = cur->next) == NULL)
            return NULL;
        nth--;
    }

    return cur;
}

int Traverse(Head head) // 전체 노드 순회하며 출력
{
    if (head == NULL) // 비어있는 연결 리스트
    {
        printf("The linked list is empty\n");
        return FALSE;
    }

    Node *cur = head;
    printf("%d", cur->data);
    cur = cur->next;

    while (cur != NULL) // 마지막 노드까지 출력
    {
        printf("->%d", cur->data);
        cur = cur->next;
    }
    printf("\n");

    return TRUE;
}


int Insert(Head *head_ptr, Data data, int nth) // n번째 위치에 노드 삽입
{
    if (head_ptr == NULL || nth < 1) // 참조 중인 head가 없거나 정의되지 않은 위치
        return FALSE;

    if (nth == 1) // 첫 번째 노드 삽입
        *head_ptr = CreateNode(data, *head_ptr);
    else
    {        
        Node *prev = GetNthNode(*head_ptr, nth - 1);

        if (prev == NULL) // 비어있는 리스트거나 삽입 가능한 위치를 벗어난 경우
            return FALSE;
            
        prev->next = CreateNode(data, prev->next);
    }

    return TRUE;
}

int Delete(Head *head_ptr, int nth) // n번째 노드 삭제
{
    if (head_ptr == NULL || *head_ptr == NULL || nth < 1) // 참조 중인 head가 없거나 비어있는 리스트, 정의되지 않은 위치
        return FALSE;
    
    Node *cur = GetNthNode(*head_ptr, nth);

    if (nth == 1) // 삭제할 노드가 첫 번째인 경우
        *head_ptr = (*head_ptr)->next;
    else
    {
        if (cur == NULL) // 삭제 가능한 위치를 벗어난 경우
            return FALSE;
        
        GetNthNode(*head_ptr, nth - 1)->next = cur->next;
    }
    free(cur);

    return TRUE;
}