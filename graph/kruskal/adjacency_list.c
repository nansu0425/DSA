#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "adjacency_list.h"

struct node *create_node(char vertex, int weight, struct node *next) // node 생성 후 반환
{
    struct node *nd = malloc(sizeof *nd);

    if (nd == NULL)
        return NULL;
    
    nd->vertex = vertex;
    nd->weight = weight;
    nd->next = next;

    return nd;
}

struct graph *create_graph(int num_of_vertices, bool is_directed) // graph 생성 후 반환
{
    struct graph *g = malloc(sizeof *g);

    if (g == NULL)
        return NULL;

    g->edges = calloc(num_of_vertices, sizeof *(g->edges));
    g->num_of_vertices = num_of_vertices;
    g->num_of_edges = 0;
    g->total_weight = 0;
    g->is_directed = is_directed;

    return g;
}

struct node *search_list(struct node *list, char vertex, struct node **prev_ptr) // list에서 vertex를 탐색한 후 node 반환
{
    struct node *cur = list;

    if (prev_ptr)
        *prev_ptr = NULL;

    // cur로 list 탐색
    while (cur) {
        if (cur->vertex == vertex)
            break;

        if (prev_ptr)
            *prev_ptr = cur;
        
        cur = cur->next;
    }

    return cur;
}

void insert_edge(struct graph *g, char from_v, char to_v, int weight) // edge 삽입
{
    // edge가 이미 존재하는지 확인 후 node를 생성하여 삽입
    if (!search_list(g->edges[from_v - 65], to_v, NULL)) {
        g->edges[from_v - 65] = create_node(to_v, weight, g->edges[from_v - 65]);
        g->num_of_edges++;
        g->total_weight += weight;
    }
        
    // undirected graph이면 반대 방향 edge 삽입
    if (!g->is_directed && !search_list(g->edges[to_v - 65], from_v, NULL))
            g->edges[to_v - 65] = create_node(from_v, weight, g->edges[to_v - 65]);
}

void delete_edge(struct graph *g, char from_v, char to_v) // edge 삭제
{
    struct node *cur;
    struct node *prev;

    // edge가 존재하는지 확인 후 node 삭제
    if (cur = search_list(g->edges[from_v - 65], to_v, &prev)) {
        if (!prev)
            g->edges[from_v - 65] = cur->next;
        else
            prev->next = cur->next;
        
        g->num_of_edges--;
        g->total_weight -= cur->weight;
        free(cur);
    }

    // undirected graph이면 반대 방향 edge도 삭제
    if (!g->is_directed && (cur = search_list(g->edges[to_v - 65], from_v, &prev))) {
        if (!prev)
            g->edges[to_v - 65] = cur->next;
        else
            prev->next = cur->next;
        
        free(cur);
    }
}

void delete_graph(struct graph *g) // graph를 삭제
{
    struct node *cur;
    struct node *next;
    int i;

    for (i = 0; i < g->num_of_vertices; i++) {
        cur = g->edges[i];

        // vertex에 연결된 node를 cur으로 순회하며 삭제
        while(cur) { 
            next = cur->next;
            free(cur);
            cur = next;
        }
    }

    free(g->edges);
    free(g);
}

void print_adjacency_list(struct graph *g) // graph의 adjacency list를 출력
{
    struct node *cur;
    int i;

    for (i = 0; i < g->num_of_vertices; i++) {
        printf("%c: ", i + 65);

        cur = g->edges[i];
        
        // vertex에 edge가 존재하는지 확인
        if (cur)
            printf("%c(%d) ", cur->vertex, cur->weight);
        else {
            printf("\n");
            continue;
        }

        // 연결된 vertex를 cur로 순회
        while (cur->next) {
            cur = cur->next;
            printf("-> %c(%d) ", cur->vertex, cur->weight);
        }
        printf("\n");
    }
    printf("the number of vertices: %d\n", g->num_of_vertices);
    printf("the number of edges: %d\n", g->num_of_edges);
    printf("total weight: %d\n", g->total_weight);
}