#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include "Trabalho.h"

int main()
{
    printf("Hello world!\n");
	start_console();

	char* name = (char*)malloc(20 * sizeof(char));

	strcpy(name, "node0\0");
	Node *node0 = create_node(0, name);

	strcpy(name, "node1\0");
	Node *node1 = create_node(1, name);
	
	printf("\n"
			"MAIN \n"
			"Node Status using functions \n"
			"node key: %d \n",
			get_node_key(node0));

	add_neighbor(node0, node1);
	add_neighbor(node0, node1);

	Node **node0_neighbors;
	node0_neighbors = get_neighbors(node0);

	for (size_t i = 0; i < get_neighbors_qtt(node0); i++)
		printf("%d ", get_node_key(node0_neighbors[i]));
	printf("\n");

	destroy_node(node0);

	printf("Bye world!\n");
	getch();

    return 0;
}
