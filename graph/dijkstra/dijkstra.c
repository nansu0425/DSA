#include <stdio.h>
#include <limits.h>
#include "dijkstra.h"
#include "graph.h"
#include "priority_queue.h"

void initialize_single_source(struct vertex* g, struct vertex* source_v) // distance 정보를 초기화
{
    int i;

    for (i = 0; i < NUM_OF_V; i++) // 모든 vertices의 distance를 int의 최댓값으로 설정
        g[i].distance = INT_MAX;

    source_v->distance = 0; // source vertex만 distance를 0으로 설정
}

bool relax(struct vertex* from_v, struct vertex* to_v, int weight) // to_v의 distance와 predecessor를 다시 설정
{
    // from_v의 distance에 from_v와 to_v 사이 edge의 weight를 더했을 때 to_v의 distance보다 작으면
    // to_v의 distance를 재설정하고 predecessor를 from_v로 바꾼다
    if (to_v->distance > from_v->distance + weight)
    {
        to_v->distance = from_v->distance + weight;
        to_v->predecessor = from_v;

        return true;
    }

    return false;
}

void dijkstra(struct vertex* g, enum vertex_name source_v_idx) // Dijkstra's algorithm으로 한 vertex로부터 모든 vertices사이의 최단 경로 계산
{   
    struct priority_queue* q;
    struct vertex* v;
    struct edge_node* e;
    int i;

    // 모든 vertices의 distance를 정수의 최댓값으로 설정하고 source vertex만 distance를 0으로 설정
    initialize_single_source(g, &g[source_v_idx]);

    // min heap으로 구현된 priority queue를 생성
    if (!(q = create_queue()))
        return;

    // 모든 vertices를 queue에 삽입
    for (i = 0; i < NUM_OF_V; i++)
        insert_vertex_ptr(q, &g[i]);

    // queue에 남은 vertex가 없을 때까지 반복
    while (q->num_of_e)
    {
        // distance가 가장 작은 vertex를 queue에서 뺀다
        v = extract_min(q);
        e = v->head;

        // edge로 연결된 모든 vertices를 탐색
        while (e)
        {
            // v vertex에 연결된 vertices의 distance를 재설정
            // queue의 heap에서 distance가 감소한 vertex의 node 위치를 재설정
            if (relax(v, e->vertex_ptr, e->weight))
                heapify(q, q->nd_num_map[e->vertex_idx], UP);

            e = e->next;
        }
    }
}