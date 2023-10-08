#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

struct vertex* create_graph() // graph 생성 후 반환
{
    struct vertex* g = calloc(NUM_OF_V, sizeof * g);
    int i;

    if (g)
    {
        // vertex의 index 정보 저장
        for (i = 0; i < NUM_OF_V; i++)
            g[i].vertex_idx = i;
    }

    return g;
}

struct edge_node* create_edge(struct vertex* g, enum vertex_name to_v_idx, int weight) // edge node 생성 후 반환
{
    struct edge_node* e = malloc(sizeof * e);

    if (e)
    {
        e->vertex_idx = to_v_idx;
        e->vertex_ptr = &g[to_v_idx];
        e->weight = weight;
        e->next = NULL;
    }

    return e;
}

void insert_edge(struct vertex* g, enum vertex_name from_v_idx, enum vertex_name to_v_idx, int weight) // vertex에 edge 삽입
{
    struct edge_node* e = create_edge(g, to_v_idx, weight);

    if (e) // adjacency list의 head에 새 edge node 삽입
    {
        e->next = g[from_v_idx].head;
        g[from_v_idx].head = e;
    }
}

void print_graph(struct vertex* g) // graph의 vertex array와 모든 adjacency lisy를 출력
{
    int v_idx;
    struct edge_node* nd;

    for (v_idx = 0; v_idx < NUM_OF_V; v_idx++)
    {
        printf("%c: ", v_idx + 65);

        if (nd = g[v_idx].head) // adjacency lisy의 head가 NULL이 아닌 경우
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

// source vertex부터 destination vertex까지의 최단 경로를 출력
void print_shortest_path(struct vertex* g, enum vertex_name dest_v_idx)
{
    struct vertex* stack[NUM_OF_V]; // 경로의 vertices 순서를 저장할 stack
    int top = -1;
    struct vertex* v;
    int v_idx;

    // destination vertex부터 source vertex까지 stack에 push
    v = &g[dest_v_idx];
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
            v_idx = stack[top--]->vertex_idx;
            printf("%c(%d)", v_idx + 65, g[v_idx].distance);

            if (top > -1) // stack이 비었으면 반복 탈출
                printf("->");
            else break;
        }
        printf("\n");
    }
}