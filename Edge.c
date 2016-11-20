#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Edge.h"

#define DEFAULT_EDGE_NAME_SIZE 20

struct edge
{
	int key;
	float weight;
	Node **nodes;
};

Edge* create_edge(int key, Node *node0, Node *node1, float weight)
{
	Edge *edge = (Edge*) malloc(sizeof(Edge));
	edge->key = key;
	edge->nodes = (Node**) malloc(2 * sizeof(Node*));
	edge->nodes[0] = node0;
	edge->nodes[1] = node1;
	edge->weight = weight;
	
	if (edge->nodes == NULL || edge == NULL)
	{
		free(edge->nodes);
		free(edge);
		return NULL;
	}

	return edge;
}

void destroy_edge(Edge *edge)
{
	free(edge->nodes);
	free(edge);
}

int get_edge_key(Edge *edge)
{
	if (edge != NULL)
		return edge->key;
	return -1;
}

void set_edge_weight(Edge *edge, float weight)
{
	if (edge != NULL)
		edge->weight = weight;
}

float get_edge_weight(Edge *edge)
{
	if (edge != NULL)
		return edge->weight;
	return INFINITY;
}

Node** get_intersected_nodes(Edge *edge)
{
	if (edge != NULL)
		return edge->nodes;
	return NULL;
}

void edge_status(Edge *edge)
{
	if (edge == NULL)
	{
		printf("Null");
		return;
	}

	printf( "edge->key : %d | "
			"edge->weight : %d | "
			"edge->node0 : %d | "
			"edge->node1 : %d \n",
			edge->key, edge->weight,
			get_node_key(edge->nodes[0]),
			get_node_key(edge->nodes[1]));
}