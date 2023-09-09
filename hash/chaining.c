#include <stdio.h>
#include <stdlib.h>

struct element {
    int key;
    char *value;
};

struct node {
    struct element e;
    struct node *next;
    struct node *prev;  
};

struct hash_table {
    struct node **slots;
    int (*hash_func)(int key, int capacity);
    int capacity;
};

struct hash_table *create_hash_table(int (*hash_func)(int key, int capacity), int capacity) // 초기화한 hash table을 반환
{
    struct hash_table *ht = malloc(sizeof *ht);
    ht->slots = calloc(capacity, sizeof *(ht->slots));
    ht->hash_func = hash_func;
    ht->capacity = capacity;

    return ht;
}

void insert(struct hash_table *ht, struct element e) // hash table에 element 삽입
{
    // hash value를 구한다
    int hv = ht->hash_func(e.key, ht->capacity);
    
    // 새로운 node 생성
    struct node *nd = malloc(sizeof *nd);
    nd->e = e;
    nd->next = nd->prev = NULL;

    // slot이 가리키고 있는 node가 이미 있는 경우
    if (ht->slots[hv] != NULL) { 
        nd->next = ht->slots[hv];
        ht->slots[hv]->prev = nd;
    }

    // slot이 새로운 node를 가리키게 한다
    ht->slots[hv] = nd;
}

struct node *search(struct hash_table *ht, int key) // hash table에서 key 탐색
{
    // hash value를 구한다
    int hv = ht->hash_func(key, ht->capacity);
    
    // cur 포인터로 node의 key를 탐색
    struct node *cur = ht->slots[hv];
    
    while (cur != NULL && cur->e.key != key)
        cur = cur->next;
    
    return cur;
}

struct element delete(struct hash_table *ht, int key) // hash table의 element 삭제
{
    // 삭제할 element의 key 탐색
    struct node *del = search(ht, key);
    struct node **slot_ptr = ht->slots + ht->hash_func(key, ht->capacity);
    struct element e = {-1, NULL};

    if (del) { // key가 hash table에 존재하는 경우
        if (del == *(slot_ptr))
            *(slot_ptr) = del->next; // 첫 번째 node인 경우
        else
            del->prev->next = del->next; // 첫 번째 node가 아닌 경우
        
        if (del->next != NULL)
            del->next->prev = del->prev; // 마지막 node가 아닌 경우
        
        // 삭제할 element를 e에 복사한 후 del 메모리 헤제
        e = del->e;
        free(del);
    }

    return e;
}

int hash_func(int key, int capacity) // hash 함수
{
    return key % capacity;
}

void print_hash_table(struct hash_table *ht) // hash table을 출력
{
    struct node *cur;
    int i;

    for (i = 0; i < ht->capacity; i++) { // 모든 slot을 순회
        if (ht->slots[i] != NULL) { // slot이 node를 가리키고 있는 경우
            cur = ht->slots[i];

            // slot의 linked list에 속하는 모든 node 출력
            printf("%d: (%d, %s)", ht->hash_func(cur->e.key, ht->capacity), 
                                       cur->e.key, 
                                       cur->e.value);
            while (cur->next) {
                cur = cur->next;
                printf(" -> (%d, %s)", cur->e.key, cur->e.value);
            }
            printf("\n");
        }
    }
}

int main()
{
    int capacity = 8;
    struct hash_table *ht = create_hash_table(hash_func, capacity);
    struct element arr[] =
    {
        {0, "Apple"},
        {1, "Mango"},
        {2, "Orange"},
        {3, "Strawberry"},
        {4, "Avocado"},
        {5, "Kiwifruit"},
        {6, "Grape"},
        {7, "Banana"},
        {8, "Cherry"},
        {9, "Watermelon"},
        {10, "Pineapple"},
        {11, "Papaya"},
        {12, "Plum"},
        {13, "Peach"},
        {14, "Grapefruit"}
    };
    int len = sizeof arr / sizeof *arr;
    int i;

    for (i = 0; i < len; i++)
        insert(ht, arr[i]);

    print_hash_table(ht);

    delete(ht, 10);
    delete(ht, 4);
    delete(ht, 12);
    delete(ht, 0);
    delete(ht, 14);
    delete(ht, 7);
    printf("\n");

    print_hash_table(ht);

    return 0;
}

/*
OUTPUT

0: (8, Cherry) -> (0, Apple)
1: (9, Watermelon) -> (1, Mango)
2: (10, Pineapple) -> (2, Orange)
3: (11, Papaya) -> (3, Strawberry)
4: (12, Plum) -> (4, Avocado)
5: (13, Peach) -> (5, Kiwifruit)
6: (14, Grapefruit) -> (6, Grape)
7: (7, Banana)

0: (8, Cherry)
1: (9, Watermelon) -> (1, Mango)
2: (2, Orange)
3: (11, Papaya) -> (3, Strawberry)
5: (13, Peach) -> (5, Kiwifruit)
6: (6, Grape)
*/