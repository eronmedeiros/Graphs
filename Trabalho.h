#ifndef TRABALHO_H
#define TRABALHO_H

#include <stdbool.h>

bool equals(char *str1, char *str2);
void start_console();
//void test();
void print_formated_graph(Graph *graph);
void organize_nodes_and_edges(Graph *graph);
void read_file();

#endif