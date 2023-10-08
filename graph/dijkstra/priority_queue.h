#pragma once

#include "graph.h"

enum heapify_direction // heapify 방향 정의
{
	DOWN,
	UP
};

struct priority_queue { // priority queue 정의
	struct vertex* min_heap[NUM_OF_V + 1]; // distance가 가장 작은 vertex의 pointer가 root(node num = 1)에 오는 min heap
	int nd_num_map[NUM_OF_V]; // index: enum vertex_name, value: min heap에서 vertex의 node number
	int num_of_e; // min heap에 존재하는 node의 수
};

struct priority_queue* create_queue(); // priority queue 생성 후 반환
void swap(struct priority_queue* q, int nd_num1 , int nd_num2); // queue의 두 node 교환 
void heapify(struct priority_queue* q, int nd_num, enum heapify_direction direction); // min heap 구조에 맞는 위치로 node 이동
void insert_vertex_ptr(struct priority_queue* q, struct vertex* v_ptr); // queue에 vertex pointer 삽입
struct vertex* extract_min(struct priority_queue* q); // queue에서 root에 위치한 node 제거 후 반환