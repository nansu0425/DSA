#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "adjacency_list.h"

enum heapify_direction // heapify 방향 정의
{
	DOWN,
	UP
};

struct queue_element { // queue의 element 정의
	char vertex;
	char from;
	int key; // from과 vertex의 weight
};

struct priority_queue { // priority queue 정의
	struct queue_element* arr;
	int* v_pos; // vertex의 array index를 저장
	int capacity;
	int num_of_e;
};

struct priority_queue* create_queue(int capacity) { // priority queue 생성 후 반환
	struct priority_queue* q = malloc(sizeof * q);
	if (q == NULL)
		return NULL;

	q->arr = malloc((capacity + 1) * sizeof * (q->arr)); // 1번 index부터 node 저장
	if (q->arr == NULL)
		return NULL;

	q->v_pos = calloc(capacity, sizeof * (q->v_pos)); // vertex가 array에 없으면 0
	if (q->v_pos == NULL)
		return NULL;

	q->capacity = capacity;
	q->num_of_e = 0;

	return q;
}

void swap(struct priority_queue *q, int nd_num1, int nd_num2) // queue의 두 element 값 교환 
{
	struct queue_element tmp = q->arr[nd_num1];

	q->arr[nd_num1] = q->arr[nd_num2];
	q->v_pos[q->arr[nd_num1].vertex - 65] = nd_num1;

	q->arr[nd_num2] = tmp;
	q->v_pos[q->arr[nd_num2].vertex - 65] = nd_num2;
}

void heapify(struct priority_queue* q, int nd_num, enum heapify_direction direction) { // key 기준으로 min-heap을 만족하는 위치로 node 이동
	int left, right, parent, target;

	if (direction == UP) { // node가 위로 이동
		parent = nd_num / 2;
		
		if (parent > 0 && q->arr[parent].key > q->arr[nd_num].key) { // node의 key가 parent의 key보다 작은 경우
			swap(q, parent, nd_num);
			heapify(q, parent, direction);
		}
	}
	else if (direction == DOWN) { // node가 아래로 이동
		left = nd_num * 2;
		right = left + 1;

		if (left <= q->num_of_e && q->arr[left].key < q->arr[nd_num].key) // left child의 key가 node의 key보다 작은 경우
			target = left;
		else
			target = nd_num;

		if (right <= q->num_of_e && q->arr[right].key < q->arr[target].key) // right child의 key가 target node의 key보다 작은 경우
			target = right;

		if (target != nd_num) { // target이 node가 아닌 경우
			swap(q, target, nd_num);
			heapify(q, target, direction);
		}
	}
}

void enqueue(struct priority_queue* q, struct queue_element e) // priority queue에 element를 넣는다
{
	if (q->capacity == q->num_of_e)
		return;

	q->arr[++q->num_of_e] = e;
	q->v_pos[e.vertex - 65] = q->num_of_e;

	heapify(q, q->num_of_e, UP);
}

struct queue_element dequeue(struct priority_queue* q) // priority queue에서 key가 가장 낮은 element를 꺼낸다
{
	struct queue_element e = q->arr[1];
	
	q->v_pos[q->arr[1].vertex - 65] = 0;
	q->arr[1] = q->arr[q->num_of_e--];
	q->v_pos[q->arr[1].vertex - 65] = 1;
	
	heapify(q, 1, DOWN);

	return e;
}

void decrease_key(struct priority_queue* q, char vertex, char from, int weight) // vertex에 해당하는 node의 key를 더 작은 weight로 decrease
{
	int nd_num = q->v_pos[vertex - 65];
	
	q->arr[nd_num].key = weight;
	q->arr[nd_num].from = from;
	
	heapify(q, nd_num, UP);
}

struct graph* prim(struct graph* g, char start_v) // Prim's algorithm으로 MST를 생성 후 반환
{
	struct priority_queue* q = create_queue(g->num_of_vertices);
	if (q == NULL)
		return NULL;

	struct graph* mst = create_graph(g->num_of_vertices, false);
	if (mst == NULL)
		return NULL;

	int i;
	struct queue_element e;
	struct node* nd;

	for (i = 0; i < g->num_of_vertices; i++) { // 모든 vertices를 queue에 넣는다
		e.key = INT_MAX;
		e.vertex = i + 65;
		e.from = 0;
		enqueue(q, e);
	}

	decrease_key(q, start_v, 0, 0);
	e = dequeue(q); // mst의 start vertex를 꺼낸다

	nd = g->edges[e.vertex - 65];
	while (nd) { // start vertex의 모든 adjacent nodes의 key를 update
		decrease_key(q, nd->vertex, e.vertex, nd->weight);
		nd = nd->next;
	}

	while (q->num_of_e > 0) { // empty queue가 될 때까지 반복
		e = dequeue(q); // mst에 연결할 수 있는 vertices 중 가장 작은 key를 갖는 vertex
		insert_edge(mst, e.from, e.vertex, e.key); // mst에 연결
		
		nd = g->edges[e.vertex - 65];
		while (nd) { // 새로 추가된 node의 모든 adjacent nodes의 key를 확인
			// 기존 key보다 새로 추가된 node 사이의 weight가 더 작은 경우 key를 더 작은 weight로 update
			if (q->v_pos[nd->vertex - 65] && nd->weight < q->arr[q->v_pos[nd->vertex - 65]].key)
				decrease_key(q, nd->vertex, e.vertex, nd->weight);
			nd = nd->next;
		}
	}

	free(q->arr);
	free(q->v_pos);
	free(q);

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

	struct graph* mst = prim(g, 'A');

	print_adjacency_list(mst);
	printf("\n");

	delete_graph(g);
	delete_graph(mst);

	return 0;
}

/*
OUTPUT

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

A: H(8) -> B(4)
B: A(4)
C: D(7) -> I(2) -> F(4)
D: E(9) -> C(7)
E: D(9)
F: C(4) -> G(2)
G: F(2) -> H(1)
H: G(1) -> A(8)
I: C(2)
the number of vertices: 9
the number of edges: 8
total weight: 37
*/