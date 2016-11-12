#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Edge.h"
#include "Node.h"

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

void check_edge(Edge *edge)
{
	printf(" \n"
		"edge->key : %d \n"
		"edge->weight : %d \n"
		"edge->node0 : %d \n"
		"edge->node1 : %d \n",
		edge->key, edge->weight,
		get_node_key(edge->nodes[0]),
		get_node_key(edge->nodes[1]));
}