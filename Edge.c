#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Edge.h"

struct edge
{
	char* key;
	float weight;
	Node **nodes;
};

Edge* create_edge(char* key, Node *node0, Node *node1, float weight)
{
	// ACEITA APENAS CHAVES POSITIVAS E PESO FINITO
	if (key == NULL || node0 == NULL || node1 == NULL || node0 == node1 || isinf(weight))
		return NULL;

	Edge *edge = (Edge*) malloc(sizeof(Edge));
	edge->key = (char*) malloc(strlen(key) * sizeof(char));
	strcpy(edge->key, key);
	edge->nodes = (Node**) malloc(2 * sizeof(Node*));
	edge->nodes[0] = node0;
	edge->nodes[1] = node1;
	edge->weight = weight;
	
	// NÃO CONSEGUIU ALOCAR MEMÓRIA
	if (edge == NULL)
		return NULL;
	else if (edge->key == NULL)
	{
		free(edge);
		edge = NULL;
	}
	else if (edge->nodes == NULL)
	{
		free(edge->key);
		edge->key = NULL;
		free(edge);
		edge = NULL;
	}

	return edge;
}

void destroy_edge(Edge **edge)
{
	if (*edge == NULL)
		return;

	Edge *e = *edge;

	free(e->key);
	e->key = NULL;
	free(e->nodes);
	e->nodes = NULL;
	free(e);
	*edge = NULL;
}

char* get_edge_key(Edge *edge)
{
	if (edge != NULL)
		return edge->key;
	return NULL;
}

void set_edge_weight(Edge *edge, float weight)
{
	if (edge != NULL && !isinf(weight))
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
		printf("Edge is Null \n");
		return;
	}

	printf( "Edge Key : %s \n"
			"Weight : %d \n"
			"Node0 : %d \n"
			"Node1 : %d \n\n",
			edge->key, edge->weight,
			get_node_key(edge->nodes[0]),
			get_node_key(edge->nodes[1]));
}