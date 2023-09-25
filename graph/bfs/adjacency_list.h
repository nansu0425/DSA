#pragma once

struct node {
    int vertex;
    struct node* next;
};

struct graph {
    struct node** edges;
    int num_of_vertices;
    bool is_directed;
};

struct node* create_node(int vertex, struct node* next); // graph 생성 후 반환

struct graph* create_graph(int num_of_vertices, bool is_directed); // graph 생성 후 반환

struct node* search_list(struct node* list, int vertex, struct node** prev_ptr); // list에서 vertex를 탐색한 후 node 반환

void insert_edge(struct graph* g, int v_from, int v_to); // edge 삽입

void delete_edge(struct graph* g, int v_from, int v_to); // edge 삭제

void delete_graph(struct graph* g); // graph를 삭제

void print_adjacency_list(struct graph* g); // graph의 adjacency list를 출력
