#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include "Node.h"
#include "Edge.h"

typedef struct graph Graph;

Graph* create_graph(int weighted);
void destroy_graph(Graph *graph);
int nodes_quantities(Graph *graph);
int edge_quantities(Graph *graph);
bool add_node(Graph *graph, Node *node);
bool add_edge(Graph *graph, Edge *edge);
void exclude_node(Graph *graph, int key);
void exclude_edge_by_key(Graph *graph, int key);
void exclude_edge_by_nodes(Graph *graph, Node *node0, Node *node1);
void exclude_edge_by_nodes_keys(Graph *graph, int node0_key, int node1_key);
Node* get_node(Graph *graph, int key);
Edge* get_edge(Graph *graph, Node *node0, Node *node1);
void check_graph_status(Graph *graph);

#endif