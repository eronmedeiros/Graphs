#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Graph.h"
#include "Node.h"
#include "Edge.h"

#define INITIAL_MAX_NODES_QTT 8
#define INITIAL_MAX_EDGES_QTT 8

typedef struct graph Graph;

struct graph
{
    Node **nodes;
	Edge **edges;
    int nodes_qtt;
	int edges_qtt;
	int max_nodes_qtt;
    int max_edges_qtt;
	int is_weighted;
};

Graph* create_graph(int weighted)
{
    Graph *graph = (Graph*) malloc (sizeof(Graph));
	graph->max_nodes_qtt = INITIAL_MAX_NODES_QTT;
	graph->nodes = (Node**) malloc(graph->max_nodes_qtt * sizeof(Node*));
	graph->max_edges_qtt = INITIAL_MAX_EDGES_QTT;
	graph->edges = (Edge**) malloc(graph->max_edges_qtt * sizeof(Edge*));
	graph->nodes_qtt = 0;
    graph->edges_qtt = 0;
	graph->is_weighted = weighted;
}

void destroy_graph(Graph *graph)
{
	if (graph == NULL)
		return;

	int i;
	Node *n0 = NULL;
	Node *n1 = graph->nodes[0];
	Edge *e0 = NULL;
	Edge *e1 = graph->edges[0];

	// DESTROY ALL NODES
	for (i = 0; n1 != NULL; i++)
	{
		n0 = n1;
		n1 = graph->nodes[i + 1];
		destroy_node(n0);
	}

	// DESTROY ALL EDGES
	for (i = 0; e1 != NULL; i++)
	{
		e0 = e1;
		e1 = graph->edges[i + 1];
		destroy_edge(e0);
	}

	free(graph->nodes);
	free(graph->edges);
    free(graph);
}

int nodes_quantities(Graph *graph)
{
	if (graph != NULL)
		return graph->nodes_qtt;
	return -1;
}

int edge_quantities(Graph *graph)
{
	if (graph != NULL)
		return graph->edges_qtt;
	return -1;
}

bool node_already_exist(Graph *graph, Node *node)
{
	int id = get_node_key(node);

	for (size_t i = 0; i < graph->nodes_qtt; i++)
	{
		if (get_node_key(graph->nodes[i]) == id)
			return true;
	}
	return false;
}

bool add_node(Graph *graph, Node *node)
{
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

}

void destroy_all_connections(Graph *graph, Node *node)
{
	Node **nodes = NULL;

	for (size_t i = 0; i < graph->edges_qtt; i++) // REMOVE TODAS AS ARESTAS QUE CONTÉM O NÓ
	{
		nodes = get_intersected_nodes(graph->edges[i]);
		
		if (node == nodes[0] || node == nodes[1])
		{
			destroy_edge(graph->edges[i]);
			for (size_t j = i; j < graph->edges_qtt - 1; j++) // AJUSTA/DESLCA A LISTA
				graph->edges[j] = graph->edges[j + 1];
			graph->edges_qtt--;
			i--;
		}
	}

	Node **neighbors = get_neighbors(node);

	for (size_t i = 0; i < get_neighbors_qtt(node); i++) // REMOVE OS VIZINHOS DO NÓ
		remove_neighbor(node, neighbors[i]);
}

void exclude_node(Graph *graph, int key)
{
	if (key > graph->nodes_qtt) // CHAVE INVÁLIDA
		return;
	
	Node *node;

	for (size_t i = 0; i < graph->nodes_qtt; i++)
	{
		if (get_node_key(graph->nodes[i]) == key)
		{
			destroy_all_connections(graph, graph->nodes[i]);
			destroy_node(graph->nodes[i]);
			graph->nodes_qtt--;

			for (size_t j = 0; j < graph->nodes_qtt - 1; j++) // AJUSTA/DESLOCA A LISTA
				graph->nodes[j] = graph->nodes[j + 1];
			break;
		}
	}
}

Node* search_node(Graph *graph, int key)
{
	for (size_t i = 0; i < graph->nodes_qtt; i++)
	{
		if (get_node_key(graph->nodes[i]) == key)
			return graph->nodes[i];
	}
	return NULL;
}

Edge* search_edge_by_key(Graph *graph, int key)
{
	for (size_t i = 0; i < graph->edges_qtt; i++)
	{
		if (get_edge_key(graph->edges[i]) == key)
			return graph->edges[i];
	}
	return NULL;
}

Edge* search_edge_by_nodes(Graph *graph, Node *node0, Node *node1)
{

}

void connect_node(Graph *graph, int node_key, int neighbor_key)
{
	Node *node0 = search_node(graph, node_key);
	Node *node1 = search_node(graph, neighbor_key);
	
	if (node0 == NULL || node1 == NULL)
		return;

	add_neighbor(node0, node1);
}

bool connect_nodes(Graph *graph, int node0_key, int node1_key, int weight)
{
	Node *node0 = search_node(graph, node0_key);
	Node *node1 = search_node(graph, node1_key);

	if (node0 == NULL || node1 == NULL)
		return false;

	Edge *edge = create_edge(graph->edges_qtt++, node0, node1, weight);

	add_neighbor(node0, node1);
	add_neighbor(node1, node0);
	add_edge(graph, edge);

	return true;
}

Edge* exclude_edge_by_key(Graph *graph, int edge_key) // RETURN THE EXCLUDED EDGE;
{

}

Edge* exclude_edge_by_nodes(Graph *graph, int node0_key, int node1_key) // RETURN THE EXCLUDED EDGE;
{

}

Node* get_node(Graph *graph, int key)
{

}

Edge* get_edge_by_key(Graph *graph, int key)
{

}

Edge* get_edge_by_nodes(Graph *graph, Node *node0, Node *node1)
{

}
