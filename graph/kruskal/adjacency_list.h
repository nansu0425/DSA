#pragma once

struct node {
    char vertex;
    int weight;
    struct node* next;
};

struct edge {
    char from_v;
    char to_v;
    int weight;
};

struct graph {
    struct node** edges;
    int num_of_vertices;
    int num_of_edges;
    int total_weight;
    bool is_directed;
};

struct node* create_node(char vertex, int weight, struct node* next); // node 생성 후 반환

struct graph* create_graph(int num_of_vertices, bool is_directed); // graph 생성 후 반환

struct node* search_list(struct node* list, char vertex, struct node** prev_ptr); // list에서 vertex를 탐색한 후 node 반환

void insert_edge(struct graph* g, char from_v, char to_v, int weight); // edge 삽입

void delete_edge(struct graph* g, char from_v, char to_v); // edge 삭제

void delete_graph(struct graph* g); // graph를 삭제

void print_adjacency_list(struct graph* g); // graph의 adjacency list를 출력
