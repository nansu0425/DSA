#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "adjacency_list.h"

struct set { // graph의 component를 구분하기 위한 set
	char vertex;
	struct set *parent;
	int rank;
};

struct set* create_set(char vertex) // 한 vertex만 존재하는 set 생성
{
	struct set* s = malloc(sizeof * s);
	if (s == NULL)
		return NULL;

	s->vertex = vertex;
	s->parent = s;
	s->rank = 0;

	return s;
}

struct set* find_set(struct set* s) // path compression을 활용하여 root 탐색
{
	if (s->parent != s)
		s->parent = find_set(s->parent);

	return s->parent;
}

void union_sets(struct set* x, struct set* y) // union by rank를 활용하여 x, y의 합집합을 만든다
{
	x = find_set(x);
	y = find_set(y);

	// rank가 더 큰 set가 root가 된다
	if (x->rank > y->rank)
		y->parent = x;
	else {
		x->parent = y;
		if (x->rank == y->rank)
			y->rank++;
	}	
}

struct edge* create_egde_arr(struct graph* g) // graph의 모든 edge 정보를 저장한 1차원 array를 생성 
{
	struct edge* edge_arr = malloc(g->num_of_edges * sizeof * edge_arr);
	if (edge_arr == NULL)
		return NULL;

	// edge 탐색 여부를 확인하기 위한 배열
	bool* check_flags = calloc(g->num_of_vertices, sizeof * check_flags);
	if (check_flags == NULL)
		return NULL;

	char i, j;
	struct node* adj_nd;

	// 인접 리스트의 모든 노드를 탐색한다
	for (i = j = 0; i < g->num_of_vertices; i++) {
		check_flags[i] = true;
		adj_nd = g->edges[i];

		// 연결된 모든 node의 정보를 edge 배열에 저장
		while (adj_nd) {
			// 이미 탐색한 edge가 아닌 경우
			if (!check_flags[adj_nd->vertex - 65]) {
				edge_arr[j].from_v = i + 65;
				edge_arr[j].to_v = adj_nd->vertex;
				edge_arr[j++].weight = adj_nd->weight;
			}

			adj_nd = adj_nd->next;
		}
	}

	free(check_flags);

	return edge_arr;
}

int compare(const void* x, const void* y) // 오름차순으로 edge 배열을 정렬하기 위한 비교 함수
{
	int x_w = ((struct edge*)x)->weight;
	int y_w = ((struct edge*)y)->weight;

	return x_w - y_w;
}

struct graph* kruskal(struct graph* g) // Kruskal's algorithm으로 MST를 생성
{
	struct graph* mst = create_graph(g->num_of_vertices, false);
	if (mst == NULL)
		return NULL;

	// disjoint-set을 저장하는 배열 
	struct set** sets = malloc(g->num_of_vertices * sizeof * sets);
	if (sets == NULL)
		return NULL;

	int i;
	// vertices를 disjoint-set으로 저장
	for (i = 0; i < g->num_of_vertices; i++)
		sets[i] = create_set(i + 65);

	// 모든 edge 정보를 배열로 저장하고 weight가 오름차순이 되도록 정렬
	struct edge* edge_arr = create_egde_arr(g);
	qsort(edge_arr, g->num_of_edges, sizeof * edge_arr, compare);

	i = 0;
	// MST의 |E|가 |V|-1이 될때까지 작은 weight를 갖는 edge부터 삽입
	while (mst->num_of_vertices - 1 > mst->num_of_edges && i < g->num_of_edges) {
		// (from_v, to_v)가 서로 다른 component를 연결하는 경우 MST에 삽입
		if (find_set(sets[edge_arr[i].from_v - 65]) != find_set(sets[edge_arr[i].to_v - 65])) {
			insert_edge(mst, edge_arr[i].from_v, edge_arr[i].to_v, edge_arr[i].weight);
			union_sets(sets[edge_arr[i].from_v - 65], sets[edge_arr[i].to_v - 65]);
		}

		i++;
	}

	// 동적 할당된 자원 해제
	for (i = 0; i < g->num_of_vertices; i++)
		free(sets[i]);
	free(sets);
	free(edge_arr);

	return mst;
}

int main()
{
	struct graph* g = create_graph(9, false);

	insert_edge(g, 'A', 'B', 4);
	insert_edge(g, 'A', 'H', 8);
	insert_edge(g, 'B', 'H', 11);
	insert_edge(g, 'B', 'C', 8);
	insert_edge(g, 'H', 'I', 7);
	insert_edge(g, 'H', 'G', 1);
	insert_edge(g, 'I', 'C', 2);
	insert_edge(g, 'I', 'G', 6);
	insert_edge(g, 'C', 'D', 7);
	insert_edge(g, 'C', 'F', 4);
	insert_edge(g, 'G', 'F', 2);
	insert_edge(g, 'D', 'F', 14);
	insert_edge(g, 'D', 'E', 9);
	insert_edge(g, 'F', 'E', 10);

	print_adjacency_list(g);
	printf("\n");

	struct graph* mst = kruskal(g);

	print_adjacency_list(mst);
	printf("\n");

	delete_graph(g);
	delete_graph(mst);

	return 0;
}

/*
OUTPUT

A: H(8) -> B(4)
B: C(8) -> H(11) -> A(4)
C: F(4) -> D(7) -> I(2) -> B(8)
D: E(9) -> F(14) -> C(7)
E: F(10) -> D(9)
F: E(10) -> D(14) -> G(2) -> C(4)
G: F(2) -> I(6) -> H(1)
H: G(1) -> I(7) -> B(11) -> A(8)
I: G(6) -> C(2) -> H(7)
the number of vertices: 9
the number of edges: 14
total weight: 93

A: B(4)
B: C(8) -> A(4)
C: B(8) -> D(7) -> F(4) -> I(2)
D: E(9) -> C(7)
E: D(9)
F: C(4) -> G(2)
G: F(2) -> H(1)
H: G(1)
I: C(2)
the number of vertices: 9
the number of edges: 8
total weight: 37
*/