#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "adjacency_list.h"

struct stack { // vertices를 저장할 stack 정의
	int* arr;
	int top;
	int capacity;
};

struct stack* create_stack(int capacity) // stack을 생성하여 반환
{
	struct stack* st = malloc(sizeof * st);
	if (st == NULL)
		return NULL;

	st->arr = malloc(capacity * sizeof * (st->arr));
	if (st->arr == NULL)
		return NULL;

	st->top = -1;

	return st;
}

bool push(struct stack* st, int vertex) // stack에 vertex를 push
{
	if (st->top + 1 == st->capacity)
		return false;

	st->arr[++st->top] = vertex;

	return true;
}

bool pop(struct stack* st, int* vertex_ptr) // stack에서 vertex를 pop
{
	if (st->top == -1)
		return false;

	*vertex_ptr = st->arr[st->top--];

	return true;
}

bool dfs(struct graph* g, int start_v) // graph를 dfs
{
	// vertices의 방문 여부를 저장하는 배열
	bool* visited_flags = calloc(g->num_of_vertices, sizeof * visited_flags);
	if (visited_flags == NULL)
		return false;

	// 방문 예정인 vertex를 push, 방문 시 pop
	struct stack* st = create_stack(g->num_of_vertices);
	if (st == NULL)
		return false;

	struct node* adj_nd;
	int cur_v;

	printf("dfs:");
	push(st, start_v);

	// stack을 비울 때까지 반복
	while (st->top > -1) {
		// stack의 top에 있는 vertex 방문
		pop(st, &cur_v);

		// 이미 방문한 vertex면 다음 반복으로 넘어간다
		if (visited_flags[cur_v])
			continue;

		visited_flags[cur_v] = true;
		printf(" %d", cur_v);

		// 현재 방문한 vertex와 edge로 연결된 모든 vertices 탐색
		adj_nd = g->edges[cur_v];
		while (adj_nd) {
			// 방문하지 않았으면 stack에 push
			if (!visited_flags[adj_nd->vertex])
				push(st, adj_nd->vertex);

			adj_nd = adj_nd->next;
		}
	}
	printf("\n");

	// 동적 할당된 자원 해제
	free(visited_flags);
	free(st->arr);
	free(st);

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
	dfs(g, 0);

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

dfs: 0 1 4 5 2 6 3 7 8
*/