#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "Node.h"

#define INITIAL_MAX_NEIGHBORS_QTT 8

struct node
{
	int key;
	float weight;
	int neighbors_qtt;
	int max_neighbors_qtt;
	Node *path;
	Node **neighbors;
};

Node* create_node(int key)
{
	Node *node = (Node*) malloc(sizeof(Node));
	node->key = key;
	node->weight = INFINITY;
	node->neighbors_qtt = 0;
	node->max_neighbors_qtt = INITIAL_MAX_NEIGHBORS_QTT;
	node->neighbors = (Node**) malloc(INITIAL_MAX_NEIGHBORS_QTT * sizeof(Node*));
	
	for (size_t i = 0; i < INITIAL_MAX_NEIGHBORS_QTT; i++)
		node->neighbors[i] = NULL;

	return node;
}

void destroy_node(Node *node)
{
	if (node == NULL)
		return;

	free(node->neighbors);
	free(node);
}

int get_node_key(Node *node)
{
	if (node != NULL)
		return node->key;
	return -1;
}

void set_node_weight(Node *node, float weight)
{
	if (node != NULL)
		node->weight = weight;
}

float get_node_weight(Node *node)
{
	if (isinf(node->weight))
		return INFINITY;
	return node->weight;
}

Node** get_neighbors(Node *node)
{
	if (node != NULL)
		return node->neighbors;
	return NULL;
}

int get_neighbors_qtt(Node *node)
{
	if (node != NULL)
		return node->neighbors_qtt;
	return -1;
}

bool add_neighbor(Node *node0, Node *neighbor)
{
	if (node0 == NULL || neighbor == NULL)
		return false;

	for (size_t i = 0; i < node0->neighbors_qtt; i++)
		if (node0->neighbors[i] == neighbor)
			return true;

	if (node0->neighbors_qtt == node0->max_neighbors_qtt)
	{
		Node **aux = node0->neighbors;
		aux = (Node**)realloc(aux, node0->max_neighbors_qtt * 2 * sizeof(Node*));
		
		if (aux == NULL) // FALHA NA ALOCAÇÃO DE MEMÓRIA
			return false;

		node0->neighbors = aux;
		node0->max_neighbors_qtt *= 2;
	}

	node0->neighbors[node0->neighbors_qtt++] = neighbor;

	return true;
}

void remove_neighbor(Node *node0, Node *neighbor)
{
	if (node0 == NULL || neighbor == NULL)
		return;
	
	for (size_t i = 0; i < node0->neighbors_qtt; i++)
		if (node0->neighbors[i] == neighbor)
		{
			for (size_t j = i; j < node0->neighbors_qtt - 1; j++) // AJUSTA/DESLOCA A LISTA
				node0->neighbors[j] = node0->neighbors[j + 1];

			node0->neighbors_qtt--;
			break;
		}
}

bool is_neighbor(Node *node, Node *neighbor)
{
	if (node == NULL || neighbor == NULL)
		return false;

	for (size_t i = 0; i < node->neighbors_qtt; i++)
		if (node->neighbors[i] == neighbor)
			return true;

	return false;
}

void check_node(Node *node)
{
	printf(" \n"
			"node->key : %d \n"
			"node->weight is infinity : %d \n"
			"node->neighbors_qtt : %d \n"
			"node->max_neighbors_qtt : %d \n",
			node->key, isinf(node->weight),
			node->neighbors_qtt, node->max_neighbors_qtt);
}