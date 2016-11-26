#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include "Node.h"
#include "Edge.h"

typedef struct graph Graph;

// CREATE AND DESTROY
Graph* create_graph(bool weighted, bool oriented);
void destroy_graph(Graph **graph);

// ADD AND REMOVE
bool add_node(Graph *graph, Node *node);
bool add_edge(Graph *graph, Edge *edge);
void remove_node(Graph *graph, Node *node);
void remove_node_by_key(Graph *graph, char *node_key);
void remove_edge(Graph *graph, Edge *node);
void remove_edge_by_key(Graph *graph, char *edge_key);
void remove_edge_by_nodes(Graph *graph, Node *node0, Node *node1);
void remove_edge_by_nodes_keys(Graph *graph, char* node0_key, char *node1_key);

// GET NODE AND EDGE
Node** get_nodes(Graph *graph);
Node* get_node(Graph *graph, char *key);
Edge** get_edges(Graph *graph);
Edge* get_edge_by_key(Graph *graph, char *edge_key);
Edge* get_edge_by_nodes(Graph *graph, Node *node0, Node *node1);
Edge* get_edge_by_nodes_keys(Graph *graph, char *node0_key, char *node1_key);

// GRAPH INFORMATIONS
int get_nodes_quantities(Graph *graph);
int get_edges_quantities(Graph *graph);
bool is_weighted(Graph *graph);
bool is_directed(Graph *graph);

// EXTRA
bool node_already_exist(Graph *graph, Node *node);
bool node_already_exist_by_key(Graph *graph, char *node_key);
bool edge_already_exist(Graph *graph, Edge *edge);
bool edge_already_exist_by_key(Graph *graph, char *edge_key);
void destroy_all_connections(Graph *graph, Node *node);

// ALGORITHM
void print_shortest_path(Graph *graph, char *start_node_key, char *end_node_key);

#endif