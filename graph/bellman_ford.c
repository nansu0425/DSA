#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define NUM_OF_V	5

enum vertices // vertex array의 index
{
    A, B, C, D, E
};

struct edge_node // vertex의 adjacency list representation에 사용되는 node
{
    enum vertices vertex_idx;
    struct vertex *vertex_ptr;
    int weight;
    struct edge_node *next;
};

struct vertex
{
    int distance; // 이 vertex까지 최단 경로의 total weight
    struct vertex *predecessor; // 최단 경로 tree에서 parent vertex
    struct edge_node *head; // edge를 adjacency list로 표현
};

struct graph
{
    struct vertex *vertex_arr;
};

struct graph *create_graph() // graph 생성 후 반환
{
    struct graph *g = malloc(sizeof *g);
    
    if (g)
    {
        g->vertex_arr = calloc(NUM_OF_V, sizeof *(g->vertex_arr)); // vertex의 모든 변수를 0또는 NULL로 초기화

        if (g->vertex_arr == NULL)
            return NULL;
    }
    
    return g;
}

struct edge_node *create_edge(struct graph *g, enum vertices to_v_idx, int weight) // edge node 생성 후 반환
{
    struct edge_node *e = malloc(sizeof *e);
    
    if (e)
    {
        e->vertex_idx = to_v_idx;
        e->vertex_ptr = &g->vertex_arr[to_v_idx];
        e->weight = weight;
        e->next = NULL;
    }

    return e;
}

void insert_edge(struct graph *g, enum vertices from_v_idx, enum vertices to_v_idx, int weight) // vertex에 edge 삽입
{
    struct edge_node *e = create_edge(g, to_v_idx, weight);

    if (e) // adjacency list의 head에 새 edge node 삽입
    {
        e->next = g->vertex_arr[from_v_idx].head;
        g->vertex_arr[from_v_idx].head = e; 
    }   
}

void print_graph(struct graph *g) // graph의 vertex array와 모든 adjacency lisy를 출력
{
    int v_idx;
    struct edge_node *nd;

    for (v_idx = 0; v_idx < NUM_OF_V; v_idx++)
    {
        printf("%c: ", v_idx + 65);

        if (nd = g->vertex_arr[v_idx].head) // adjacency lisy의 head가 NULL이 아닌 경우
        {
            while (1)
            {
                printf("%c(%d)", nd->vertex_idx + 65, nd->weight); // vertex와 weight 출력
                
                if (nd = nd->next) // 연결된 다른 edge node로 이동
                    printf("->");
                else break;
            }
        }
        printf("\n");
    }
}

void initialize_single_source(struct graph *g, struct vertex *source_v) // distance 정보를 초기화
{
    int i;

    for (i = 0; i < NUM_OF_V; i++) // 모든 vertices의 distance를 int의 최댓값으로 설정
        g->vertex_arr[i].distance = INT_MAX;

    source_v->distance = 0; // 최단 경로의 시작 vertex만 distance를 0으로 설정
}

void relax(struct vertex *from_v, struct vertex *to_v, int weight) // to_v의 distance와 predecessor를 다시 설정
{
    // from_v의 distance에 from_v와 to_v 사이 edge의 weight를 더했을 때 to_v의 distance보다 작으면
    // to_v의 distance를 predecessor를 from_v로 바꾸면서 distance를 재설정
    if (to_v->distance > from_v->distance + weight)
    {
        to_v->distance = from_v->distance + weight;
        to_v->predecessor = from_v;
    }
}

// Bellman-Ford algorithm으로 source vertex 기준으로
// 모든 vertices의 최단 경로를 구한다
// 경로 관계는 vertex의 predecessor 연결 관계로 표현
bool bellman_ford(struct graph *g, enum vertices source_v_idx) 
{
    int i, j;
    struct edge_node *nd;

    // 모든 vertices의 distance 값을 정수의 최댓값으로 설정
    // source vertex의 distance 값은 0
    initialize_single_source(g, &g->vertex_arr[source_v_idx]);
    
    for (i = 1; i < NUM_OF_V; i++) // |V|-1 만큼 반복
    {
        // 모든 edges에 relax를 수행
        for (j = 0; j < NUM_OF_V; j++)
        {
            nd = g->vertex_arr[j].head; // adjacency list의 첫 번째 edge node

            while (nd) {
                relax(&g->vertex_arr[j], nd->vertex_ptr, nd->weight);
                nd = nd->next;
            }
        }
    }

    // 모든 edges를 확인
    for (i = 0; i < NUM_OF_V; i++)
    {
        nd = g->vertex_arr[i].head; // adjacency list의 첫 번째 edge node

        while (nd)
        {   
            // 여전히 relax가 가능한 상태면 negative-weight cycle이 존재
            if (nd->vertex_ptr->distance > g->vertex_arr[i].distance + nd->weight) 
                return false;
            
            nd = nd->next;
        }
    }

    return true;
}

// source vertex부터 destination vertex까지의 최단 경로를 출력
void print_shortest_path(struct graph *g, enum vertices dest_v_idx)
{
    struct vertex *stack[NUM_OF_V]; // 경로의 vertices 순서를 저장할 stack
    int top = -1;
    struct vertex *v;
    int vertex_idx;

    // destination vertex부터 source vertex까지 stack에 push
    v = &g->vertex_arr[dest_v_idx];
    while (v)
    {
        stack[++top] = v;
        v = v->predecessor;
    }

    if (top > 0) // stack에 source vertex만 존재하는 경우는 제외
    {
        printf("destination %c: ", dest_v_idx + 65);

        while (1) {
            // stack에서 pop한 후 vertex의 index를 계산하여 vertex와 destination 값을 출력
            vertex_idx = stack[top--] - g->vertex_arr;
            printf("%c(%d)", vertex_idx + 65, g->vertex_arr[vertex_idx].distance);

            if (top > -1) // stack이 비었으면 반복 탈출
                printf("->");
            else break;
        }
        printf("\n");
    }
}

void find_all_shortest_paths(struct graph *g, enum vertices source_v)
{
    int i;

    if (bellman_ford(g, source_v)) // Bellman-Ford algorithm으로 최단 경로 계산
    {
        printf("source: %c\n", source_v + 65);

        // 모든 vertices의 source vertex로부터 최단 경로를 출력
        for (i = 0; i < NUM_OF_V; i++)
            print_shortest_path(g, i);
    } 
    else // negative-weight cycle이 존재하는 경우
        printf("A negative cycle exists in the graph.\n");
}

int main()
{
    struct graph *g = create_graph();

    insert_edge(g, A, B, 6);
    insert_edge(g, A, D, 7);
    insert_edge(g, B, D, 8);
    insert_edge(g, B, E, -4);
    insert_edge(g, B, C, 5);
    insert_edge(g, C, B, -2);
    insert_edge(g, D, C, -3);
    insert_edge(g, D, E, 9);
    insert_edge(g, E, A, 2);
    insert_edge(g, E, C, 7);

    print_graph(g);
    printf("\n");

    find_all_shortest_paths(g, A);
    printf("\n");

    printf("-------------------------------------------------\n\n");

    struct graph *negative_cycle = create_graph();

    insert_edge(negative_cycle, A, B, 6);
    insert_edge(negative_cycle, A, D, 7);
    insert_edge(negative_cycle, B, D, 8);
    insert_edge(negative_cycle, B, E, -4);
    insert_edge(negative_cycle, B, C, -5); // B->C: -5
    insert_edge(negative_cycle, C, B, -2); // C->B: -2
    insert_edge(negative_cycle, D, C, -3);
    insert_edge(negative_cycle, D, E, 9);
    insert_edge(negative_cycle, E, A, 2);
    insert_edge(negative_cycle, E, C, 7);

    print_graph(negative_cycle);
    printf("\n");

    find_all_shortest_paths(negative_cycle, A);

    return 0;
}

/*
OUTPUT

A: D(7)->B(6)
B: C(5)->E(-4)->D(8)
C: B(-2)
D: E(9)->C(-3)
E: C(7)->A(2)

source: A
destination B: A(0)->D(7)->C(4)->B(2)
destination C: A(0)->D(7)->C(4)
destination D: A(0)->D(7)
destination E: A(0)->D(7)->C(4)->B(2)->E(-2)

-------------------------------------------------

A: D(7)->B(6)
B: C(-5)->E(-4)->D(8)
C: B(-2)
D: E(9)->C(-3)
E: C(7)->A(2)

A negative cycle exists in the graph.
*/