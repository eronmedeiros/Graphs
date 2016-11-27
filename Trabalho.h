#ifndef TRABALHO_H
#define TRABALHO_H

#include "Graph.h"
#include <stdbool.h>

// DEFAULT
void start_console();

// EXTRA
bool equals(char *str1, char *str2);

// ALGORITHM
void print_shortest_path(Graph *graph, char *start_node_key, char *end_node_key);

#endif