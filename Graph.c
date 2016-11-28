#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "Graph.h"
#include "Trabalho.h"

#define INITIAL_MAX_NODES_QTT 8
#define INITIAL_MAX_EDGES_QTT 8

struct graph
{
	Node **nodes;
	Edge **edges;
	int nodes_qtt;
	int edges_qtt;
	int max_nodes_qtt;
	int max_edges_qtt;
	bool is_weighted;
	bool is_directed;
};

// CREATE AND DESTROY
Graph* create_graph(bool weighted, bool directed)
{
	if (weighted != 0 && weighted != 1)
		return NULL;

	Graph *graph = (Graph*)malloc(sizeof(Graph));
	graph->max_nodes_qtt = INITIAL_MAX_NODES_QTT;
	graph->nodes = (Node**)malloc(graph->max_nodes_qtt * sizeof(Node*));
	graph->max_edges_qtt = INITIAL_MAX_EDGES_QTT;
	graph->edges = (Edge**)malloc(graph->max_edges_qtt * sizeof(Edge*));
	graph->nodes_qtt = 0;
	graph->edges_qtt = 0;
	graph->is_weighted = weighted;
	graph->is_directed = directed;

	if (graph == NULL)
		return NULL;
	else if (graph->nodes == NULL)
	{
		free(graph);
		graph = NULL;
	}
	else if (graph->edges == NULL)
	{
		free(graph->nodes);
		graph->nodes = NULL;
		free(graph);
		graph = NULL;
	}

	for (size_t i = 0; i < graph->max_nodes_qtt; i++)
		graph->nodes[i] = NULL;

	for (size_t i = 0; i < graph->max_edges_qtt; i++)
		graph->edges[i] = NULL;

	return graph;
}

void destroy_graph(Graph **graph)
{
	if ((*graph) == NULL)
		return;
	Graph *g = *graph;

	// DESTROY ALL NODES
	while (g->nodes_qtt > 0)
		destroy_node(&(g->nodes[--(g->nodes_qtt)]));

	// DESTROY ALL EDGES
	while (g->edges_qtt > 0)
		destroy_edge(&g->edges[--g->edges_qtt]);

	free(g->nodes);
	g->nodes = NULL;
	free(g->edges);
	g->edges = NULL;
	free(g);
	*graph = NULL;
}

// ADD AND REMOVE
bool add_node(Graph *graph, Node *node)
{
	if (graph == NULL || node == NULL)
		return false;

	if (node_already_exist(graph, node)) // O NÓ JÁ EXISTE
		return true;

	Node **aux = graph->nodes;

	if (graph->nodes_qtt == graph->max_nodes_qtt)
	{
		aux = (Node**)realloc(aux, graph->max_nodes_qtt * 2 * sizeof(Node*));

		if (aux == NULL) // FALHA NA ALOCAÇÃO DE MEMÓRIA
			return false;

		graph->nodes = aux;
		graph->max_nodes_qtt *= 2;
	}

	graph->nodes[graph->nodes_qtt++] = node;

	return true;
}

bool add_edge(Graph *graph, Edge *edge)
{
	if (graph == NULL || edge == NULL)
		return false;

	if (edge_already_exist(graph, edge)) // A EDGE JÁ EXISTE
		return true;

	Edge **aux = graph->edges;

	if (graph->edges_qtt == graph->max_edges_qtt)
	{
		aux = (Edge**)realloc(aux, graph->max_edges_qtt * 2 * sizeof(Edge*));

		if (aux == NULL) // FALHA NA REALOCAÇÃO DE MEMÓRIA
			return false;

		graph->edges = aux;
		graph->max_edges_qtt *= 2;
	}

	// FAZ OS AMBOS OS NÓS SEREM VIZINHOS.
	Node **nodes = get_intersected_nodes(edge);

	if (add_neighbor(nodes[0], nodes[1]))
	{
		if (add_neighbor(nodes[1], nodes[0]))
		{
			graph->edges[graph->edges_qtt++] = edge; // EDGE ADICIONADA NO GRAFO
			return true; // AMBOS OS VIZINHOS FORAM ADICIONADOS COM SUCESSO
		}
		else
			remove_neighbor(nodes[0], nodes[1]);
	}

	return false;
}

void remove_node(Graph *graph, Node *node)
{
	if (graph == NULL || node == NULL)
		return;

	for (size_t i = 0; i < graph->nodes_qtt; i++)
		if (graph->nodes[i] == node)
		{
			destroy_all_connections(graph, graph->nodes[i]);
			destroy_node(&graph->nodes[i]);

			for (size_t j = i; j < graph->nodes_qtt - 1; j++) // AJUSTA/DESLOCA A LISTA
				graph->nodes[j] = graph->nodes[j + 1];

			graph->nodes[--graph->nodes_qtt] = NULL;

			break;
		}
}

void remove_node_by_key(Graph *graph, char *node_key)
{
	if (graph == NULL)
		return;

	for (size_t i = 0; i < graph->nodes_qtt; i++)
		if (equals(get_node_key(graph->nodes[i]), node_key))
		{
			destroy_all_connections(graph, graph->nodes[i]);
			destroy_node(&graph->nodes[i]);

			for (size_t j = i; j < graph->nodes_qtt - 1; j++) // AJUSTA/DESLOCA A LISTA
				graph->nodes[j] = graph->nodes[j + 1];

			graph->nodes[--graph->nodes_qtt] = NULL;

			break;
		}
}

void remove_edge(Graph *graph, Edge *edge)
{
	if (graph == NULL || edge == NULL)
		return;

	for (size_t i = 0; i < graph->edges_qtt; i++)
		if (graph->edges[i] == edge)
		{
			Node **nodes = get_intersected_nodes(edge);

			remove_neighbor(nodes[0], nodes[1]); // REMOVENDO VIZINHOS QUE A EDGE CONECTA
			remove_neighbor(nodes[1], nodes[0]);

			destroy_edge(&graph->edges[i]);

			for (size_t j = i; j < graph->edges_qtt - 1; j++) // AJUSTA/DESLOCA A LISTA
				graph->edges[j] = graph->edges[j + 1];

			graph->edges[--graph->edges_qtt] = NULL;
			break;
		}
}

void remove_edge_by_key(Graph *graph, char *edge_key)
{
	if (graph == NULL)
		return;

	for (size_t i = 0; i < graph->edges_qtt; i++)
		if (equals(get_edge_key(graph->edges[i]), edge_key))
		{
			Node **nodes = get_intersected_nodes(graph->edges[i]);

			remove_neighbor(nodes[0], nodes[1]); // REMOVENDO VIZINHOS QUE A EDGE CONECTA
			remove_neighbor(nodes[1], nodes[0]);

			destroy_edge(&graph->edges[i]);

			for (size_t j = i; j < graph->edges_qtt - 1; j++) // AJUSTA/DESLOCA A LISTA
				graph->edges[j] = graph->edges[j + 1];

			graph->edges[--graph->edges_qtt] = NULL;
			break;
		}
}

void remove_edge_by_nodes(Graph *graph, Node *node0, Node *node1)
{
	if (graph == NULL || node0 == NULL || node1 == NULL)
		return;

	Node **nodes = NULL;

	for (size_t i = 0; i < graph->edges_qtt; i++)
	{
		nodes = get_intersected_nodes(graph->edges[i]);

		if ((nodes[0] == node0 && nodes[1] == node1) ||
			(nodes[0] == node1 && nodes[1] == node0))
		{
			remove_neighbor(nodes[0], nodes[1]); // REMOVENDO VIZINHOS QUE A EDGE CONECTA
			remove_neighbor(nodes[1], nodes[0]);

			destroy_edge(&graph->edges[i]);

			for (size_t j = i; j < graph->edges_qtt - 1; j++) // AJUSTA/DESLOCA A LISTA
				graph->edges[j] = graph->edges[j + 1];

			graph->edges[--graph->edges_qtt] = NULL;
			break;
		}
	}
}

void remove_edge_by_nodes_keys(Graph *graph, char *node0_key, char *node1_key)
{
	if (graph == NULL)
		return;

	Node **nodes = NULL;

	for (size_t i = 0; i < graph->edges_qtt; i++)
	{
		nodes = get_intersected_nodes(graph->edges[i]);

		if ((equals(get_node_key(nodes[0]), node0_key) && equals(get_node_key(nodes[1]), node1_key)) ||
			(equals(get_node_key(nodes[0]), node1_key) && equals(get_node_key(nodes[1]), node0_key)))
		{
			remove_neighbor(nodes[0], nodes[1]); // REMOVENDO VIZINHOS QUE A EDGE CONECTA
			remove_neighbor(nodes[1], nodes[0]);

			destroy_edge(&graph->edges[i]);

			for (size_t j = i; j < graph->edges_qtt - 1; j++) // AJUSTA/DESLOCA A LISTA
				graph->edges[j] = graph->edges[j + 1];

			graph->edges[--graph->edges_qtt] = NULL;
			break;
		}
	}
}

// GET NODE AND EDGE
Node** get_nodes(Graph *graph)
{
	if (graph != NULL)
		return graph->nodes;
	return NULL;
}

Node* get_node(Graph *graph, char *key)
{
	if (graph != NULL)
		for (size_t i = 0; i < graph->nodes_qtt; i++)
			if (equals(get_node_key(graph->nodes[i]), key))
				return graph->nodes[i];

	return NULL;
}

Edge** get_edges(Graph *graph)
{
	if (graph != NULL)
		return graph->edges;
	return NULL;
}

Edge* get_edge_by_key(Graph *graph, char *key)
{
	if (graph != NULL)
		for (size_t i = 0; i < graph->edges_qtt; i++)
			if (equals(get_edge_key(graph->edges[i]), key))
				return graph->edges[i];

	return NULL;
}

Edge* get_edge_by_nodes(Graph *graph, Node *node0, Node *node1)
{
	if (graph != NULL || node0 != NULL || node1 != NULL || node0 != node1)
		for (size_t i = 0; i < graph->edges_qtt; i++)
		{
			Node **nodes = get_intersected_nodes(graph->edges[i]);

			if ((nodes[0] == node0 && nodes[1] == node1) ||
				(nodes[0] == node1 && nodes[1] == node0))
				return graph->edges[i];
		}

	return NULL;
}

Edge* get_edge_by_nodes_keys(Graph *graph, char *node0_key, char *node1_key)
{
	if (graph != NULL)
		for (size_t i = 0; i < graph->edges_qtt; i++)
		{
			Node **nodes = get_intersected_nodes(graph->edges[i]);

			if ((equals(get_node_key(nodes[0]), node0_key) && equals(get_node_key(nodes[1]), node1_key)) ||
				(equals(get_node_key(nodes[0]), node1_key) && equals(get_node_key(nodes[1]), node0_key)))
				return graph->edges[i];
		}

	return NULL;
}

// GRAPH INFORMATIONS
int get_nodes_quantities(Graph *graph)
{
	if (graph != NULL)
		return graph->nodes_qtt;

	return -1;
}

int get_edges_quantities(Graph *graph)
{
	if (graph != NULL)
		return  graph->edges_qtt;

	return -1;
}

bool is_weighted(Graph *graph)
{
	if (graph != NULL)
		return graph->is_weighted;
	return false;
}

bool is_directed(Graph *graph)
{
	if (graph != NULL)
		return graph->is_directed;
	return false;
}

// EXTRA
bool node_already_exist(Graph *graph, Node *node)
{
	if (graph != NULL || node != NULL)
		for (size_t i = 0; i < graph->nodes_qtt; i++)
			if (graph->nodes[i] == node)
				return true;

	return false;
}

bool node_already_exist_by_key(Graph *graph, char *node_key)
{
	if (graph != NULL && node_key != NULL)
		for (size_t i = 0; i < graph->nodes_qtt; i++)
			if (equals(get_node_key(graph->nodes[i]), node_key))
				return true;

	return false;
}

bool edge_already_exist(Graph *graph, Edge *edge)
{
	if (graph != NULL || edge != NULL)
		for (size_t i = 0; i < graph->edges_qtt; i++)
			if (graph->edges[i] == edge)
				return true;

	return false;
}

bool edge_already_exist_by_key(Graph *graph, char *edge_key)
{
	if (graph != NULL && edge_key != NULL)
		for (size_t i = 0; i < graph->edges_qtt; i++)
			if (equals(get_edge_key(graph->edges[i]), edge_key))
				return true;

	return false;
}

// AUXILIARY
void destroy_all_connections(Graph *graph, Node *node)
{
	if (graph == NULL || node == NULL)
		return;

	for (size_t i = 0; i < graph->edges_qtt; i++) // REMOVE TODAS AS ARESTAS QUE CONTÉM O NÓ
	{
		Node **nodes = get_intersected_nodes(graph->edges[i]);

		if (node == nodes[0] || node == nodes[1])
		{
			destroy_edge(&graph->edges[i]);

			for (size_t j = i--; j < graph->edges_qtt - 1; j++) // AJUSTA/DESLCA A LISTA
				graph->edges[j] = graph->edges[j + 1];

			graph->edges[--graph->edges_qtt] = NULL;
		}
	}

	Node **neighbors = get_neighbors(node);

	for (size_t i = 0; i < get_neighbors_qtt(node); i++) // REMOVE OS VIZINHOS DO NÓ
		remove_neighbor(node, neighbors[i]);
}
