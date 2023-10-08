#pragma once

#define NUM_OF_V 5 // vertices의 개수

enum vertex_name // graph에서 사용할 모든 vertices의 name, vertex array의 index로 사용
{
    A, B, C, D, E
};

struct edge_node // adjacency list representation에 사용되는 node
{
    enum vertex_name vertex_idx;
    struct vertex* vertex_ptr;
    int weight;
    struct edge_node* next;
};

struct vertex
{
    enum vertex_name vertex_idx;
    int distance; // 이 vertex까지 최단 경로의 total weight
    struct vertex* predecessor; // 최단 경로 tree에서 parent vertex
    struct edge_node* head; // vertex의 adjacency list
};

struct vertex* create_graph(); // graph 생성 후 반환
struct edge_node* create_edge(struct vertex* g, enum vertex_name to_v_idx, int weight); // edge node 생성 후 반환
void insert_edge(struct vertex* g, enum vertex_name from_v_idx, enum vertex_name to_v_idx, int weight); // vertex에 edge 삽입
void print_graph(struct vertex* g); // graph의 vertex array와 모든 adjacency lisy를 출력
void print_shortest_path(struct vertex* g, enum vertex_name dest_v_idx); // source vertex부터 destination vertex까지의 최단 경로를 출력