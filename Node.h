#ifndef NODE_H
#define NODE_H

#include <stdbool.h>

typedef struct node Node;

Node* create_node(int key);
void destroy_node(Node *node);
int get_node_key(Node *node);
void set_node_weight(Node *node, float weight);
float get_node_weight(Node *node);
Node** get_neighbors(Node *node);
int get_neighbors_qtt(Node *node);
bool add_neighbor(Node *node0, Node *neighbor);
void remove_neighbor(Node *node0, Node *neighbor);
bool is_neighbor(Node *node, Node *neighbor);
void check_node(Node *node);

#endif