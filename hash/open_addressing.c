#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct slot // hash table의 slot
{
    int key;
    bool deleted;
};

struct hash_table // hash value와 key를 대응시키는 hash table
{
    struct slot *slot_arr;
    int (*hash_function)(int, int, int);
    int size;
};

struct hash_table *create_hash_table(int (*hash_function)(int, int, int), int size) // hash table 생성 후 반환
{
    struct hash_table *ht = malloc(sizeof *(ht));
    int i;

    if (ht) {
        ht->slot_arr = malloc(size * sizeof *(ht->slot_arr));
        
        if (ht->slot_arr) {
            for (i = 0; i < size; i++) { // slot의 초기 값: key = -1, deleted = false
                ht->slot_arr[i].key = -1;
                ht->slot_arr[i].deleted = false;
            }
        } else 
            return NULL;
        
        ht->hash_function = hash_function;
        ht->size = size;
    }

    return ht;
}

int hash_get_key(struct hash_table *ht, int hash_value) // hash value에 해당하는 key를 반환
{
    return ht->slot_arr[hash_value].key;
}

void hash_set_key(struct hash_table *ht, int hash_value, int key) // hash value에 해당하는 slot에 key 저장
{
    ht->slot_arr[hash_value].key = key;
}

bool hash_is_deleted(struct hash_table *ht, int hash_value) // key의 deleted 여부를 반환
{
    return ht->slot_arr[hash_value].deleted;
}

void hash_set_deleted(struct hash_table *ht, int hash_value, bool deleted) // key의 deleted 여부를 설정
{
    ht->slot_arr[hash_value].deleted = deleted;
}

int hash_insert(struct hash_table *ht, int key) // hash table에 key 삽입
{
    int i = 0;
    int hv;

    while (i != ht->size) { // hash table 크기만큼 반복
        hv = ht->hash_function(key, i, ht->size); // hash value를 구한다

        if (hash_get_key(ht, hv) == -1) { // hash value에 해당하는 slot이 비어있는 경우
            hash_set_key(ht, hv, key); // key를 저장
            hash_set_deleted(ht, hv, false); // deleted 여부를 false로 설정
            
            return hv;
        }

        i++;
    }

    return -1;
}

int hash_search(struct hash_table *ht, int key) // key에 해당하는 hash value를 탐색
{
    int i = 0;
    int hv;

    while (i != ht->size) { // hash table 크기만큼 반복
        hv = ht->hash_function(key, i, ht->size); // hash value를 구한다

        if (hash_get_key(ht, hv) == key) // hash value에 해당하는 slot에 key가 있는 경우
            return hv;
        else if (hash_get_key(ht, hv) == -1 && // hash value에 해당하는 slot이 비어있고
                !hash_is_deleted(ht, hv)) // deleted 여부가 false인 경우
            return -1;
        
        i++;
    }

    return -1;
}

int hash_delete(struct hash_table *ht, int key) // key를 hash table에서 삭제
{
    int hv = hash_search(ht, key); // key의 hash value 탐색

    if (hv > -1) // hash table에 key가 있는 경우
    {
        hash_set_key(ht, hv, -1); // hash value에 해당하는 slot에 -1 저장
        hash_set_deleted(ht, hv, true); // key의 deleted 여부를 true로 설정

        return hv;
    }

    return -1;
}

int linear_probing(int key, int i, int size) // 선형적으로 조사
{
    int h = key % size;

    return (h + i) % size;
}

int quadratic_probing(int key, int i, int size) // 제곱하여 조사
{
    int h = key % size;

    return (h + i*i) % size;
}

int double_hashing(int key, int i, int size) // hashing을 두 번 사용
{
    int h1 = key % size;
    int h2 = 1 + (key % (size - 1)); // 0 < h2 < size를 만족하고 size(소수)와 서로소
    
    return (h1 + i*h2) % size;
}

void print_hash_table(struct hash_table *ht) // hash table의 key 정보를 출력
{
    int i, k;
    
    printf("(hash value)\t: (key)\n");
    for (i = 0; i < ht->size; i++)
    {
        printf("%d\t\t:", i);

        if ((k = hash_get_key(ht, i)) > -1)
            printf(" %d\n", k);
        else
            printf("\n");    
    }
}

int main()
{
    int key_arr[10] = {3, 9, 18, 23, 29, 31, 43, 69, 80, 109}; 
    
    struct hash_table *ht_linear = create_hash_table(linear_probing, 20);
    struct hash_table *ht_quadratic = create_hash_table(quadratic_probing, 20);
    struct hash_table *ht_double = create_hash_table(double_hashing, 23);

    int i;

    for(i = 0; i < 10; i++)
    {
        hash_insert(ht_linear, key_arr[i]);
        hash_insert(ht_quadratic, key_arr[i]);
        hash_insert(ht_double, key_arr[i]);
    }

    printf("linear probing\n");
    print_hash_table(ht_linear);
    printf("\n");

    printf("quadratic probing\n");
    print_hash_table(ht_quadratic);
    printf("\n");

    printf("double hasing\n");
    print_hash_table(ht_double);
    printf("\n");

    hash_delete(ht_linear, 9);
    hash_delete(ht_linear, 69);
    hash_delete(ht_quadratic, 9);
    hash_delete(ht_quadratic, 69);
    hash_delete(ht_double, 9);
    hash_delete(ht_double, 69);
    
    printf("9, 69 was deleted\n\n");

    printf("linear probing\n");
    print_hash_table(ht_linear);
    printf("\n");

    printf("quadratic probing\n");
    print_hash_table(ht_quadratic);
    printf("\n");

    printf("double hasing\n");
    print_hash_table(ht_double);
    printf("\n");

    return 0;
}

/*
OUTPUT

linear probing
(hash value)    : (key)
0               : 80
1               :
2               :
3               : 3
4               : 23
5               : 43
6               :
7               :
8               :
9               : 9
10              : 29
11              : 31
12              : 69
13              : 109
14              :
15              :
16              :
17              :
18              : 18
19              :

quadratic probing
(hash value)    : (key)
0               : 80
1               :
2               :
3               : 3
4               : 23
5               : 109
6               :
7               : 43
8               :
9               : 9
10              : 29
11              : 31
12              :
13              : 69
14              :
15              :
16              :
17              :
18              : 18
19              :

double hasing
(hash value)    : (key)
0               : 23
1               :
2               :
3               : 3
4               : 69
5               :
6               : 29
7               :
8               : 31
9               : 9
10              :
11              : 80
12              :
13              :
14              :
15              :
16              :
17              : 109
18              : 18
19              :
20              : 43
21              :
22              :

9, 69 was deleted

linear probing
(hash value)    : (key)
0               : 80
1               :
2               :
3               : 3
4               : 23
5               : 43
6               :
7               :
8               :
9               :
10              : 29
11              : 31
12              :
13              : 109
14              :
15              :
16              :
17              :
18              : 18
19              :

quadratic probing
(hash value)    : (key)
0               : 80
1               :
2               :
3               : 3
4               : 23
5               : 109
6               :
7               : 43
8               :
9               :
10              : 29
11              : 31
12              :
13              :
14              :
15              :
16              :
17              :
18              : 18
19              :

double hasing
(hash value)    : (key)
0               : 23
1               :
2               :
3               : 3
4               :
5               :
6               : 29
7               :
8               : 31
9               :
10              :
11              : 80
12              :
13              :
14              :
15              :
16              :
17              : 109
18              : 18
19              :
20              : 43
21              :
22              :
*/