#include <stdlib.h>
#include <memory.h>
#include "priority_queue.h"

struct priority_queue* create_queue() // priority queue 생성 후 반환
{
	struct priority_queue* q = malloc(sizeof * q);
	
	if (q)
	{
		// 모든 변수를 0 또는 NULL로 초기화
		memset(q->min_heap, 0, sizeof q->min_heap);
		memset(q->nd_num_map, 0, sizeof q->nd_num_map);
		q->num_of_e = 0;
	}

	return q;
}
	
void swap(struct priority_queue* q, int nd_num1, int nd_num2) // queue의 두 node 교환 
{
	struct vertex* tmp = q->min_heap[nd_num1];

	// nd_num2에 해당하는 node가 nd_num1 위치로 이동
	q->min_heap[nd_num1] = q->min_heap[nd_num2];
	q->nd_num_map[q->min_heap[nd_num1]->vertex_idx] = nd_num1;

	// nd_num1에 해당하는 node가 nd_num2 위치로 이동
	q->min_heap[nd_num2] = tmp;
	q->nd_num_map[q->min_heap[nd_num2]->vertex_idx] = nd_num2;
}

void heapify(struct priority_queue* q, int nd_num, enum heapify_direction direction) // min heap 구조에 맞는 위치로 node 이동
{
	int left, right, parent, target;

	if (direction == UP) { // parent node와 비교
		parent = nd_num / 2;

		// nd_num에 해당하는 node의 distance가 parent의 distance보다 작은 경우
		if (parent > 0 && q->min_heap[parent]->distance > q->min_heap[nd_num]->distance) { 
			swap(q, parent, nd_num);
			heapify(q, parent, direction);
		}
	}
	else if (direction == DOWN) { // child node와 비교
		left = nd_num * 2;
		right = left + 1;
		
		// left child의 distance가 nd_num에 해당하는 node의 distance보다 작은 경우
		if (left <= q->num_of_e && q->min_heap[left]->distance < q->min_heap[nd_num]->distance) 
			target = left;
		else
			target = nd_num;

		// right child의 distance가 target node의 distance보다 작은 경우
		if (right <= q->num_of_e && q->min_heap[right]->distance < q->min_heap[target]->distance) 
			target = right;

		if (target != nd_num) { // target이 node가 아닌 경우
			swap(q, target, nd_num);
			heapify(q, target, direction);
		}
	}
}

void insert_vertex_ptr(struct priority_queue* q, struct vertex* v_ptr) // queue에 vertex pointer 삽입
{
	if (NUM_OF_V == q->num_of_e)
		return;

	// min heap의 마지막 node 뒤에 v_ptr 추가
	q->min_heap[++q->num_of_e] = v_ptr;
	q->nd_num_map[v_ptr->vertex_idx] = q->num_of_e;

	// 삽입한 node가 위로 올라가면서 자기 자리를 찾는다
	heapify(q, q->num_of_e, UP);
}

struct vertex* extract_min(struct priority_queue* q) // queue의 min heap에서 root에 위치한 node 제거 후 반환
{
	struct vertex* root = q->min_heap[1];

	// root node 제거 후 min heap의 마지막 node를 root 자리로 옮긴다 
	q->nd_num_map[q->min_heap[1]->vertex_idx] = 0;
	q->min_heap[1] = q->min_heap[q->num_of_e--];
	q->nd_num_map[q->min_heap[1]->vertex_idx] = 1;

	// root로 옮겨진 node는 아래로 내려가면서 자리를 찾는다
	heapify(q, 1, DOWN);

	return root;
}