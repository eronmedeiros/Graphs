#ifndef NODE_H
#define NODE_H

#include <stdbool.h>

typedef struct node Node;

Node* create_node(char *key);
void destroy_node(Node **node);
char* get_node_key(Node *node);
void set_node_weight(Node *node, float weight);
float get_node_weight(Node *node);
Node** get_neighbors(Node *node);
int get_neighbors_qtt(Node *node);
void set_path(Node *node, Node *path);
Node* get_path(Node *node);
bool add_neighbor(Node *node, Node *neighbor);
void remove_neighbor(Node *node, Node *neighbor);
bool is_neighbor(Node *node, Node *neighbor);

#endif