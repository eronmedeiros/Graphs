#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Graph.h"
#include "Node.h"
#include "Edge.h"

void start_console()
{
	Graph *graph;
	Node *node;
	Edge *edge;
	char *action;
	char *param1;
	char *param2;

	while (true)
	{
		printf(">> ");
		fgets(action, sizeof(action), stdin);
	}
}