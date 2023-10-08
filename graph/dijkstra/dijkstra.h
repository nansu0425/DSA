#pragma once

#include <stdbool.h>
#include "graph.h"

void initialize_single_source(struct vertex* g, struct vertex* source_v); // distance 정보를 초기화
bool relax(struct vertex* from_v, struct vertex* to_v, int weight); // to_v의 distance와 predecessor를 다시 설정
void dijkstra(struct vertex* g, enum vertex_name source_v_idx); // Dijkstra's algorithm으로 한 vertex로부터 모든 vertices사이의 최단 경로 계산