#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct graph {
    int **edges;
    int num_of_vertices;
    bool is_directed;
};

struct graph *create_graph(int num_of_vertices, bool is_directed) // graph를 생성하여 반환
{
    struct graph *g = malloc(sizeof *g);
    int i;

    // edge 정보를 저장하기 위한 |V|^2 크기의 adjacency matrix를 메모리에 할당
    g->edges = malloc(num_of_vertices * sizeof *(g->edges));
    for (i = 0; i < num_of_vertices; i++)
        g->edges[i] = calloc(num_of_vertices, sizeof *(g->edges[i]));

    g->num_of_vertices = num_of_vertices;
    g->is_directed = is_directed;

    return g;
}

void insert_edge(struct graph *g, int v_from, int v_to) // edge 삽입
{
    *(g->edges[v_from] + v_to) = 1;

    if (!g->is_directed) // undirected graph인 경우
        *(g->edges[v_to] + v_from) = 1;
}

void delete_edge(struct graph *g, int v_from, int v_to) // edge 삭제
{
    *(g->edges[v_from] + v_to) = 0;

    if (!g->is_directed) // undirected graph인 경우
        *(g->edges[v_to] + v_from) = 0;
}

void delete_graph(struct graph *g) // graph 삭제
{
    int i;

    for (i = 0; i < g->num_of_vertices; i++)
        free(g->edges[i]);
    free(g->edges);
    free(g);
}

void print_adjacency_matrix(struct graph *g) // graph의 adjacency matrix 출력
{
    int i, j;

    printf("    ");
    for (i = 0; i < g->num_of_vertices; i++)
        printf("%d ", i);
    printf("\n\n");
    
    for (i = 0; i < g->num_of_vertices; i++) {
        printf("%d   ", i);

        for (j = 0; j < g->num_of_vertices; j++)
            printf("%d ", *(g->edges[i] + j));
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
    print_adjacency_matrix(directed_g);
    delete_graph(directed_g);

    struct graph *undirected_g = create_graph(5, false);

    // (0, 1), (0, 3), (2, 4), (3, 2)
    insert_edge(undirected_g, 2, 4);
    insert_edge(undirected_g, 1, 0);
    insert_edge(undirected_g, 3, 4);
    delete_edge(undirected_g, 3, 4);
    insert_edge(undirected_g, 0, 3);
    insert_edge(undirected_g, 3, 2);
    insert_edge(undirected_g, 1, 4);
    delete_edge(undirected_g, 1, 4);

    printf("\nundirected graph\n\n");
    print_adjacency_matrix(undirected_g);
    delete_graph(undirected_g);

    return 0;
}

/*
OUTPUT

directed graph

    0 1 2 3 4

0   0 1 0 0 0
1   0 0 0 0 0
2   0 0 0 0 1
3   0 0 0 0 0
4   0 0 0 1 0

undirected graph

    0 1 2 3 4

0   0 1 0 1 0 
1   1 0 0 0 0
2   0 0 0 1 1
3   1 0 1 0 0
4   0 0 1 0 0
*/