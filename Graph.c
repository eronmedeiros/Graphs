#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
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
	
	if (graph->nodes == NULL || graph->edges == NULL)
	{
		free(graph->nodes);
		free(graph->edges);
		free(graph);
		return NULL;
	}

	return graph;
}

void destroy_graph(Graph *graph)
{
	if (graph == NULL)
		return;

	// DESTROY ALL NODES
	while (graph->nodes_qtt >= 0)
		destroy_node(graph->nodes[--graph->nodes_qtt]);

	// DESTROY ALL EDGES
	while (graph->edges_qtt >= 0)
		destroy_edge(graph->edges[--graph->edges_qtt]);

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
	if (graph == NULL || node == NULL)
		return false;

	int id = get_node_key(node);

	for (size_t i = 0; i < graph->nodes_qtt; i++)
		if (get_node_key(graph->nodes[i]) == id)
			return true;

	return false;
}

bool add_node(Graph *graph, Node *node)
{
	if (graph == NULL || node == NULL)
		return false;

	if (node_already_exist(graph, node)) // O NÓ JÁ EXISTE
		return true;

	Node **aux = graph->nodes;

	if (graph->nodes_qtt == graph->max_nodes_qtt)
	{
		aux = (Node**) realloc(aux, graph->max_nodes_qtt * 2 * sizeof(Node*));

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

	Edge **aux = graph->edges;

	if (graph->edges_qtt == graph->max_edges_qtt)
	{
		aux = (Node**) realloc(aux, graph->max_edges_qtt * 2 * sizeof(Node*));

		if (aux == NULL) // FALHA NA ALOCAÇÃO DE MEMÓRIA
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

void destroy_all_connections(Graph *graph, Node *node)
{
	if (graph == NULL || node == NULL)
		return;

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

void exclude_node(Graph *graph, Node *node)
{
	int key = get_node_key(node);

	if (graph == NULL || node == NULL || key > graph->nodes_qtt)
		return;

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
	if (graph != NULL && key < graph->nodes_qtt && key > 0) // CONSIDERA QUE A CHAVE INICIE EM UM (1)
	{
		for (size_t i = 0; i < graph->nodes_qtt; i++)
			if (get_node_key(graph->nodes[i]) == key)
				return graph->nodes[i];
	}
	return NULL;
}

Edge* search_edge_by_key(Graph *graph, int key)
{
	for (size_t i = 0; i < graph->edges_qtt; i++)
		if (get_edge_key(graph->edges[i]) == key)
			return graph->edges[i];

	return NULL;
}

Edge* search_edge_by_nodes(Graph *graph, Node *node0, Node *node1)
{
	Node **nodes = NULL;

	for (size_t i = 0; i < graph->edges_qtt; i++)
	{
		nodes = get_intersected_nodes(graph->edges[i]);

		if (nodes[0] == node0 && nodes[1] == node1 || nodes[0] == node1 && nodes[1] == node0)
			return graph->edges[i];
	}

	return NULL;
}

Edge* exclude_edge_by_key(Graph *graph, int key) // RETURN THE EXCLUDED EDGE;
{
	for (size_t i = 0; i < graph->edges_qtt; i++)
		if (get_edge_key(graph->edges[i]) == key)
		{
			Node **nodes = get_intersected_nodes(graph->edges[i]);

			remove_neighbor(nodes[0], nodes[1]); // REMOVENDO VIZINHOS QUE A EDGE CONECTA
			remove_neighbor(nodes[1], nodes[0]);

			destroy_edge(graph->edges[i]);
			for (size_t j = i; j < graph->edges_qtt - 1; j++) // AJUSTA/DESLCA A LISTA
				graph->edges[j] = graph->edges[j + 1];
			graph->edges_qtt--;
			break;
		}
}

void exclude_edge_by_nodes_keys(Graph *graph, int node0_key, int node1_key)
{
	Node **nodes = NULL;

	for (size_t i = 0; i < graph->edges_qtt; i++)
	{
		nodes = get_intersected_nodes(graph->edges[i]);

		if (get_node_key(nodes[0]) == node0_key && get_node_key(nodes[1]) == node1_key ||
			get_node_key(nodes[0]) == node1_key && get_node_key(nodes[1]) == node0_key)
		{
			remove_neighbor(nodes[0], nodes[1]); // REMOVENDO VIZINHOS QUE A EDGE CONECTA
			remove_neighbor(nodes[1], nodes[0]);

			destroy_edge(graph->edges[i]);
			for (size_t j = i; j < graph->edges_qtt - 1; j++) // AJUSTA/DESLCA A LISTA
				graph->edges[j] = graph->edges[j + 1];
			graph->edges_qtt--;
			break;
		}
	}
}

Edge* exclude_edge_by_nodes(Graph *graph, Node *node0, Node *node1)
{
	Node **nodes = NULL;

	for (size_t i = 0; i < graph->edges_qtt; i++)
	{
		nodes = get_intersected_nodes(graph->edges[i]);

		if (nodes[0] == node0 && nodes[1] == node1 || nodes[0] == node1 && nodes[1] == node0)
		{
			remove_neighbor(node0, node1); // REMOVENDO VIZINHOS QUE A EDGE CONECTA
			remove_neighbor(node1, node0);

			destroy_edge(graph->edges[i]);
			for (size_t j = i; j < graph->edges_qtt - 1; j++) // AJUSTA/DESLCA A LISTA
				graph->edges[j] = graph->edges[j + 1];
			graph->edges_qtt--;
			break;
		}
	}

}

Node* get_node(Graph *graph, int key)
{
	if ()
}

Edge* get_edge_by_key(Graph *graph, int key)
{

}

Edge* get_edge_by_nodes(Graph *graph, Node *node0, Node *node1)
{

}
