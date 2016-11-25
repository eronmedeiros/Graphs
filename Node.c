#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "Node.h"

#define DEFAULT_MAX_NEIGHBORS_QTT 8

struct node
{
	char* key;
	int neighbors_qtt;
	int max_neighbors_qtt;
	float weight;
	Node *path;
	Node **neighbors;
};

Node* create_node(char* key)
{
	if (key == NULL)
		return NULL;

	Node *node = (Node*) malloc(sizeof(Node));
	node->key = (char*) malloc(strlen(key) * sizeof(char));
	strcpy(node->key, key);
	node->neighbors_qtt = 0;
	node->max_neighbors_qtt = DEFAULT_MAX_NEIGHBORS_QTT;
	node->weight = INFINITY;
	node->path = NULL;
	node->neighbors = (Node**) malloc(DEFAULT_MAX_NEIGHBORS_QTT * sizeof(Node*));
	
	for (size_t i = 0; i < DEFAULT_MAX_NEIGHBORS_QTT; i++)
		node->neighbors[i] = NULL;

	// NÃO CONSEGUIU ALOCAR MEMÓRIA
	if (node == NULL)
		return NULL;
	else if (node->key == NULL)
	{
		free(node);
		node = NULL;
		return NULL;
	}
	else if(node->neighbors == NULL)
	{
		free(node->key);
		node->key = NULL;
		free(node);
		node = NULL;
	}

	return node;
}

void destroy_node(Node **node)
{
	if ((*node) == NULL)
		return;

	free((*node)->key);
	(*node)->key = NULL;
	free((*node)->neighbors);
	(*node)->neighbors = NULL;
	free(*node);
	(*node) = NULL;
}

char* get_node_key(Node *node)
{
	if (node != NULL)
		return node->key;
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

void set_path(Node *node, Node *path)
{
	if (node != NULL)
		node->path = path;
}

Node* get_path(Node *node)
{
	if (node != NULL)
		return node->path;
	return NULL;
}

bool add_neighbor(Node *node, Node *neighbor)
{
	if (node == NULL || neighbor == NULL || node == neighbor)
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
	if (node == NULL || neighbor == NULL)
		return;

	for (size_t i = 0; i < node->neighbors_qtt; i++)
		if (node->neighbors[i] == neighbor)
		{
			for (size_t j = i; j < node->neighbors_qtt - 1; j++) // AJUSTA/DESLOCA A LISTA
				node->neighbors[j] = node->neighbors[j + 1];

			node->neighbors[--node->neighbors_qtt] = NULL;
			break;
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

void node_status(Node *node)
{
	if (node == NULL)
	{
		printf("Node is Null \n");
		return;
	}
	
	printf( "Node Key : %s \n"
			"Weight : %.2f \n"
			"Neighbors qtt : %d \n"
			"Max neighbors qtt : %d \n"
			"Neighbors keys: ",
			node->key, node->weight,
			node->neighbors_qtt, node->max_neighbors_qtt);
	
	for (size_t i = 0; i < node->neighbors_qtt; i++)
		printf("%s ", node->neighbors[i]->key);

	printf("\n\n");
}