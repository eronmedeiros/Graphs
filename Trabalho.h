#ifndef TRABALHO_H
#define TRABALHO_H

#include "Graph.h"
#include <stdbool.h>

bool equals(char *str1, char *str2);
void print_graph(Graph *graph);
void organize_nodes_and_edges(Graph *graph);
void start_console();
//void test();
void read_file();

#endif