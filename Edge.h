#ifndef EDGE_H
#define EDGE_H

#include "Node.h"

typedef struct edge Edge;

Edge* create_edge(int key, Node *node0, Node *node1, char *name, float weight);
void destroy_edge(Edge *edge);
int get_edge_key(Edge *edge);
char* get_edge_name(Edge *edge);
void set_edge_weight(Edge *edge, float weight);
float get_edge_weight(Edge *edge);
Node** get_intersected_nodes(Edge *edge);
void check_edge_status(Edge *edge);

#endif