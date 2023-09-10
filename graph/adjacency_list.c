#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
    int vertex;
    struct node *next;
};

struct graph {
    struct node **edges;
    int num_of_vertices;
    bool is_directed;
};

struct node *create_node(int vertex, struct node *next) // graph 생성 후 반환
{
    struct node *nd = malloc(sizeof *nd);
    
    nd->vertex = vertex;
    nd->next = next;

    return nd;
}

struct graph *create_graph(int num_of_vertices, bool is_directed) // graph 생성 후 반환
{
    struct graph *g = malloc(sizeof *g);

    g->edges = calloc(num_of_vertices, sizeof *(g->edges));
    g->num_of_vertices = num_of_vertices;
    g->is_directed = is_directed;

    return g;
}

struct node *search_list(struct node *list, int vertex, struct node **prev_ptr) // list에서 vertex를 탐색한 후 node 반환
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

void insert_edge(struct graph *g, int v_from, int v_to) // edge 삽입
{
    // edge가 이미 존재하는지 확인 후 node를 생성하여 삽입
    if (!search_list(g->edges[v_from], v_to, NULL)) 
        g->edges[v_from] = create_node(v_to, g->edges[v_from]);
    
    // undirected graph이면 반대 방향 edge 삽입
    if (!g->is_directed && !search_list(g->edges[v_to], v_from, NULL)) {
            g->edges[v_to] = create_node(v_from, g->edges[v_to]);
    }
}

void delete_edge(struct graph *g, int v_from, int v_to) // edge 삭제
{
    struct node *cur;
    struct node *prev;

    // edge가 존재하는지 확인 후 node 삭제
    if (cur = search_list(g->edges[v_from], v_to, &prev)) {
        if (!prev)
            g->edges[v_from] = cur->next;
        else
            prev->next = cur->next;
        
        free(cur);
    }

    // undirected graph이면 반대 방향 edge도 삭제
    if (!g->is_directed && (cur = search_list(g->edges[v_to], v_from, &prev))) {
        if (!prev)
            g->edges[v_to] = cur->next;
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
        printf("%d: ", i);

        cur = g->edges[i];
        
        // vertex에 edge가 존재하는지 확인
        if (cur)
            printf("%d ", cur->vertex);
        else {
            printf("\n");
            continue;
        }

        // 연결된 vertex를 cur로 순회
        while (cur->next) {
            cur = cur->next;
            printf("-> %d ", cur->vertex);
        }
        printf("\n");
    }
}

int main()
{
    struct graph *directed_g = create_graph(5, true);

    // (0, 1), (2, 4), (4, 3)
    insert_edge(directed_g, 0, 1);
    insert_edge(directed_g, 1, 3);
    delete_edge(directed_g, 1, 3);
    insert_edge(directed_g, 2, 4);
    insert_edge(directed_g, 3, 1);
    delete_edge(directed_g, 3, 1);
    insert_edge(directed_g, 4, 3);

    printf("directed graph\n\n");
    print_adjacency_list(directed_g);
    delete_graph(directed_g);

    struct graph *undirected_g = create_graph(5, false);

    // (0, 1), (0, 3), (2, 4), (3, 2)
    insert_edge(undirected_g, 2, 4);
    insert_edge(undirected_g, 1, 0);
    insert_edge(undirected_g, 0, 3);
    insert_edge(undirected_g, 3, 4); 
    insert_edge(undirected_g, 3, 2);
    insert_edge(undirected_g, 1, 4);
    delete_edge(undirected_g, 3, 4);
    delete_edge(undirected_g, 1, 4);

    printf("\nundirected graph\n\n");
    print_adjacency_list(undirected_g);
    delete_graph(undirected_g);

    return 0;
}

/*
OUTPUT

directed graph

0: 1
1:
2: 4
3:
4: 3

undirected graph

0: 3 -> 1
1: 0
2: 3 -> 4 
3: 2 -> 0
4: 2
*/