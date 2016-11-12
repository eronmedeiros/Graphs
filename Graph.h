#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

Graph* create_graph(int weighted);
void destroy_graph(Graph *graph);
int nodes_quantities(Graph *graph);
int edge_quantities(Graph *graph);
bool add_node(Graph *graph, Node *node);
bool add_edge(Graph *graph, Edge *edge);
void exclude_node(Graph *graph, int key);
void exclude_edge_by_key(Graph *graph, int key);
void exclude_edge_by_nodes(Graph *graph, Node *node0, Node *node1);
Node* get_node(Graph *graph, int key);
Edge* get_edge(Graph *graph, Node *node0, Node *node1);

#endif