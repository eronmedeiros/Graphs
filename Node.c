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

	if (node->neighbors == NULL || node == NULL)
	{
		free(node->neighbors);
		free(node);
		return NULL;
	}

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
	if (node != NULL)
		if (isinf(node->weight))
			return INFINITY;
		else
			return node->weight;
	
	return -1;
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

bool add_neighbor(Node *node, Node *neighbor)
{
	if (node == NULL || neighbor == NULL)
		return false;

	for (size_t i = 0; i < node->neighbors_qtt; i++)
		if (node->neighbors[i] == neighbor)
			return true;

	if (node->neighbors_qtt == node->max_neighbors_qtt)
	{
		Node **aux = node->neighbors;
		aux = (Node**) realloc(aux, node->max_neighbors_qtt * 2 * sizeof(Node*));
		
		if (aux == NULL) // FALHA NA ALOCAÇÃO DE MEMÓRIA
			return false;

		node->neighbors = aux;
		node->max_neighbors_qtt *= 2;
	}

	node->neighbors[node->neighbors_qtt++] = neighbor;

	return true;
}

void remove_neighbor(Node *node, Node *neighbor)
{
	if (node != NULL && neighbor != NULL)
	{
		for (size_t i = 0; i < node->neighbors_qtt; i++)
			if (node->neighbors[i] == neighbor)
			{
				for (size_t j = i; j < node->neighbors_qtt - 1; j++) // AJUSTA/DESLOCA A LISTA
					node->neighbors[j] = node->neighbors[j + 1];

				node->neighbors_qtt--;
				break;
			}
	}
}

bool is_neighbor(Node *node, Node *neighbor)
{
	if (node != NULL && neighbor != NULL)
	{
		for (size_t i = 0; i < node->neighbors_qtt; i++)
			if (node->neighbors[i] == neighbor)
				return true;
	}
	return false;
}

void check_node_status(Node *node)
{
	if (node == NULL)
	{
		printf("Null");
		return;
	}
		
	printf(" \n"
			"node->key : %d \n"
			"node->weight is infinity : %d \n"
			"node->neighbors_qtt : %d \n"
			"node->max_neighbors_qtt : %d \n",
			node->key, isinf(node->weight),
			node->neighbors_qtt, node->max_neighbors_qtt);
}