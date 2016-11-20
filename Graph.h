#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include "Node.h"
#include "Edge.h"

typedef struct graph Graph;

// CREATE AND DESTROY
Graph* create_graph(int weighted);
void destroy_graph(Graph **graph);

// ADD AND REMOVE
bool add_node(Graph *graph, Node *node);
bool add_edge(Graph *graph, Edge *edge);
void remove_node(Graph *graph, Node *node);
void remove_node_by_key(Graph *graph, int node_key);
void remove_edge(Graph *graph, Edge *node);
void remove_edge_by_key(Graph *graph, int edge_key);
void remove_edge_by_nodes(Graph *graph, Node *node0, Node *node1);
void remove_edge_by_nodes_keys(Graph *graph, int node0_key, int node1_key);

// GET NODE AND EDGE
Node* get_node(Graph *graph, int key);
Edge* get_edge_by_key(Graph *graph, int edge_key);
Edge* get_edge_by_nodes(Graph *graph, Node *node0, Node *node1);
Edge* get_edge_by_nodes_keys(Graph *graph, int node0_key, int node1_key);

// GRAPH INFORMATIONS
int nodes_quantities(Graph *graph);
int edge_quantities(Graph *graph);
void graph_status(Graph *graph);

// EXTRA
bool node_already_exist(Graph *graph, Node *node);
bool node_already_exist_by_key(Graph *graph, int node_key);
bool edge_already_exist(Graph *graph, Edge *edge);
bool edge_already_exist_by_key(Graph *graph, int edge_key);
Edge** shortest_path(Graph *graph, Node *node0, Node *node1);

#endif