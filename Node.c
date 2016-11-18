#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "Node.h"

#define DEFAULT_MAX_NEIGHBORS_QTT 8
#define DEFAULT_NODE_NAME_SIZE 20

struct node
{
	int key;
	char *name;
	float weight;
	int neighbors_qtt;
	int max_neighbors_qtt;
	Node *path;
	Node **neighbors;
};

Node* create_node(int key, char *name)
{
	Node *node = (Node*) malloc(sizeof(Node));
	node->key = key;
	node->name = name;
	node->weight = INFINITY;
	node->neighbors_qtt = 0;
	node->max_neighbors_qtt = DEFAULT_MAX_NEIGHBORS_QTT;
	node->neighbors = (Node**) malloc(DEFAULT_MAX_NEIGHBORS_QTT * sizeof(Node*));
	
	for (size_t i = 0; i < DEFAULT_MAX_NEIGHBORS_QTT; i++)
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

void set_node_name(Node *node, char *new_name)
{
	if (node == NULL || new_name == NULL)
		return;

	free(node->name);
	node->name = new_name;
}

char* get_node_name(Node *node)
{
	if (node != NULL)
		return node->name;
	return NULL;
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
		
	printf(
			"node->key : %d | "
			"node->weight : %d | "
			"node->weight is infinity : %d | "
			"node->neighbors_qtt : %d | "
			"node->max_neighbors_qtt : %d | "
			"Neighbors keys: ",
			node->key, node->weight, isinf(node->weight),
			node->neighbors_qtt, node->max_neighbors_qtt);
	
	for (size_t i = 0; i < node->neighbors_qtt; i++)
		printf("%d ", node->neighbors[i]->key);

	printf("\n\n");
}