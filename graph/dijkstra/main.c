#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "dijkstra.h"

int main()
{
	struct vertex* graph = create_graph();
	int i;
	
	if (!graph)
		exit(1);

	insert_edge(graph, A, B, 10);
	insert_edge(graph, A, D, 5);
	insert_edge(graph, B, C, 1);
	insert_edge(graph, B, D, 2);
	insert_edge(graph, C, E, 4);
	insert_edge(graph, D, B, 3);
	insert_edge(graph, D, C, 9);
	insert_edge(graph, D, E, 2);
	insert_edge(graph, E, A, 7);
	insert_edge(graph, E, C, 6);

	print_graph(graph);
	printf("\n");

	dijkstra(graph, A);

	printf("source: %c\n", A + 65);
	for (i = 0; i < NUM_OF_V; i++)
		print_shortest_path(graph, i);

	return 0;
}

/*
OUTPUT

A: D(5)->B(10)
B: D(2)->C(1)
C: E(4)
D: E(2)->C(9)->B(3)
E: C(6)->A(7)

source: A
destination B: A(0)->D(5)->B(8)
destination C: A(0)->D(5)->B(8)->C(9)
destination D: A(0)->D(5)
destination E: A(0)->D(5)->E(7)
*/