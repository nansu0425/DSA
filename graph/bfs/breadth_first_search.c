#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "adjacency_list.h"

struct queue { // vertices 저장을 위한 queue
	int* arr;
	int front;
	int rear;
	int capacity;
};

struct queue *create_queue(int capacity) // queue 생성
{
	struct queue *q = malloc(sizeof *q);
	if (q == NULL)
		return NULL;

	q->arr = malloc(capacity * sizeof * (q->arr));
	if (q->arr == NULL)
		return NULL;

	q->front = q->rear = 0;
	q->capacity = capacity;

	return q;
}

bool enqueue(struct queue* q, int vertex) // queue의 rear에 vertex를 넣는다
{
	if (q->capacity == q->rear)
		return false;

	q->arr[q->rear] = vertex;
	q->rear++;

	return true;
}

bool dequeue(struct queue* q, int* vertex_ptr) // queue의 front에서 vertex를 뺀다
{
	if (q->front == q->rear)
		return false;

	*vertex_ptr = q->arr[q->front];
	q->front++;

	return true;
}

bool bfs(struct graph* g, int strat_v) // graph를 bfs
{
	// vertex 방문 여부를 저장하기 위한 배열
	bool* visited_flags = calloc(g->num_of_vertices, sizeof *visited_flags);
	if (visited_flags == NULL)
		return false;
	
	// vertex를 방문하면 enqueue, vertex와 연결된 다른 vertices를 탐색할 때 dequeue
	struct queue* q = create_queue(g->num_of_vertices);
	if (q == NULL)
		return false;

	int cur_v;
	struct node* adj_n;

	// start_v부터 탐색 시작
	printf("bfs: %d", strat_v);
	enqueue(q, strat_v);
	visited_flags[strat_v] = true;

	// queue를 비울 때까지 반복
	while (q->front != q->rear) {
		dequeue(q, &cur_v);
		adj_n = g->edges[cur_v];
		
		// cur_v와 연결된 vertices 탐색
		while (adj_n) {
			// 방문하지 않은 vertex인 경우
			if (!visited_flags[adj_n->vertex]) {
				printf(" %d", adj_n->vertex);
				enqueue(q, adj_n->vertex);
				visited_flags[adj_n->vertex] = true;
			}

			adj_n = adj_n->next;
		}
	}
	printf("\n");

	// 동적 할당된 자원 해제
	free(q->arr);
	free(q);
	free(visited_flags);

	return true;
}

int main()
{
	struct graph* g = create_graph(9, false);

	insert_edge(g, 0, 1);
	insert_edge(g, 0, 2);
	insert_edge(g, 0, 3);
	insert_edge(g, 1, 4);
	insert_edge(g, 1, 5);
	insert_edge(g, 2, 6);
	insert_edge(g, 3, 6);
	insert_edge(g, 3, 7);
	insert_edge(g, 3, 8);
	insert_edge(g, 7, 8);

	print_adjacency_list(g);
	printf("\n");
	bfs(g, 0);

	delete_graph(g);

	return 0;
}

/*
OUTPUT

0: 3 -> 2 -> 1
1: 5 -> 4 -> 0
2: 6 -> 0
3: 8 -> 7 -> 6 -> 0
4: 1
5: 1
6: 3 -> 2
7: 8 -> 3
8: 7 -> 3

bfs: 0 3 2 1 8 7 6 5 4
*/