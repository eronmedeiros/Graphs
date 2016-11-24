#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "Graph.h"

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
	int is_weighted;
};

// CREATE AND DESTROY
Graph* create_graph(int weighted)
{
	if (weighted != 0 && weighted != 1)
		return NULL;

    Graph *graph = (Graph*) malloc (sizeof(Graph));
	graph->max_nodes_qtt = INITIAL_MAX_NODES_QTT;
	graph->nodes = (Node**) malloc(graph->max_nodes_qtt * sizeof(Node*));
	graph->max_edges_qtt = INITIAL_MAX_EDGES_QTT;
	graph->edges = (Edge**) malloc(graph->max_edges_qtt * sizeof(Edge*));
	graph->nodes_qtt = 0;
    graph->edges_qtt = 0;
	graph->is_weighted = weighted;
	
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

	// DESTROY ALL NODES
	while ((*graph)->nodes_qtt > 0)
		destroy_node(&(*graph)->nodes[--(*graph)->nodes_qtt]);

	// DESTROY ALL EDGES
	while ((*graph)->edges_qtt > 0)
		destroy_edge(&(*graph)->edges[--(*graph)->edges_qtt]);

	free((*graph)->nodes);
	(*graph)->nodes = NULL;
	free((*graph)->edges);
	(*graph)->edges = NULL;
    free((*graph));
	(*graph) = NULL;
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
			
			for (size_t j = 0; j < graph->nodes_qtt - 1; j++) // AJUSTA/DESLOCA A LISTA
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
			//destroy_all_connections(graph, graph->nodes[i]);
			destroy_node(&graph->nodes[i]);

			for (size_t j = 0; j < graph->nodes_qtt - 1; j++) // AJUSTA/DESLOCA A LISTA
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

		if (nodes[0] == node0 && nodes[1] == node1 ||
			nodes[0] == node1 && nodes[1] == node0)
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
Node* get_node(Graph *graph, char *key)
{
	if (graph != NULL)
		for (size_t i = 0; i < graph->nodes_qtt; i++)
			if (equals(get_node_key(graph->nodes[i]), key))
				return graph->nodes[i];

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

			if (nodes[0] == node0 && nodes[1] == node1 ||
				nodes[0] == node1 && nodes[1] == node0)
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
				(equals(get_node_key(nodes[0]), node1_key) && equals(get_node_key(nodes[1]), node0_key)) )
				return graph->edges[i];
		}

	return NULL;
}

// GRAPH INFORMATIONS
int nodes_quantities(Graph *graph)
{
	if (graph != NULL)
		return graph->nodes_qtt;

	return -1;
}

int edge_quantities(Graph *graph)
{
	if (graph != NULL)
		return  graph->edges_qtt;

	return -1;
}

void graph_status(Graph *graph)
{
	if (graph == NULL)
	{
		printf("Graph is NULL \n");
		return;
	}

	printf( "\n"
			"Graph Status \n\n"
			"Nodes quantities: %d \n"
			"Edges quantities: %d \n"
			"Is Weighted: %d \n",
			graph->nodes_qtt, graph->edges_qtt, graph->is_weighted);

	printf("\nNode Status: \n");
	for (size_t i = 0; i < graph->nodes_qtt; i++)
		node_status(graph->nodes[i]);

	printf("\nEdge Status: \n");
	for (size_t i = 0; i < graph->edges_qtt; i++)
		edge_status(graph->edges[i]);
	
	printf("\n");
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
	if (graph != NULL)
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
	if (graph != NULL)
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

bool equals(char *str1, char *str2)
{
	return !strcmp(str1, str2) ? true : false;
}

// ALGORITHM AUXILIARY
bool relax(Graph *graph, Node *node0, Node *node1)
{
	Edge *edge = get_edge_by_nodes(graph, node0, node1);

	if ((get_node_weight(node0) + get_edge_weight(edge)) < get_node_weight(node1))
	{
		set_node_weight(node1, get_node_weight(node0) + get_edge_weight(edge));
		set_path(node1, node0);
		return true;
	}

	return false;
}

Edge** search_path(Graph *graph, Node *start, Node *end)
{
	Node *node = end;
	Edge **path = (Edge**)malloc(graph->edges_qtt * sizeof(Edge*));
	Edge *edge = NULL;

	for (size_t i = 0; i < graph->edges_qtt; i++)
		path[i] = NULL;

	for (size_t i = 0; node != NULL; i++, node = get_path(node))
		path[i] = get_edge_by_nodes(graph, get_path(node), node);

	return path;
}

void print_path(Edge **path)
{
	float cost = 0;
	size_t i;

	for (i = 0; path[i] != NULL; i++)
		cost += get_edge_weight(path[i]);

	printf("Cost: %d \n"
		"Path Sequence: ", (int)cost);

	while (i != 0)
		printf("%s ", get_edge_key(path[--i]));

	printf("\n");
}

// ALGORITHM
void print_shortest_path(Graph *graph, char *start_node_key, char *end_node_key)
{
	Node **intersected;
	Node *start = get_node(graph, start_node_key);
	Node *end = get_node(graph, end_node_key);

	set_node_weight(start, 0);

	for (size_t j = 0; j < graph->nodes_qtt - 1; j++)
		for (size_t i = 0; i < graph->edges_qtt; i++)
		{
			intersected = get_intersected_nodes(graph->edges[i]);
			relax(graph, intersected[0], intersected[1]);
			relax(graph, intersected[1], intersected[0]);
		}
	
	for (size_t i = 0; i < graph->edges_qtt; i++)
	{
		intersected = get_intersected_nodes(graph->edges[i]);
		if (relax(graph, intersected[0], intersected[1]) ||
			relax(graph, intersected[0], intersected[1]))
			printf("Invalid Shortest Path! \n");
	}

	Edge **path = search_path(graph, start, end);
	print_path(path);
	free(path);
	path = NULL;
}
