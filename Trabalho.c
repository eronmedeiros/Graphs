#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "Graph.h"
#include "Node.h"
#include "Edge.h"

#define DEFAULT_INPUT_SIZE 50
#define COMMAND_LENGTH 6

// EXTRA
bool equals(char *str1, char *str2)
{
	return !strcmp(str1, str2) ? true : false;
}

char** split(char *string, char delimiter)
{
	int i, j, k;
	char **split_string = (char **)malloc(COMMAND_LENGTH * sizeof(char*));

	for (i = 0; i < COMMAND_LENGTH; i++)
		split_string[i] = (char *)malloc((strlen(string) + 1) * sizeof(char));

	for (i = j = k = 0; string[i] != '\0'; i++, k++)
	{
		if (string[i] != delimiter)
			split_string[j][k] = string[i];
		else
		{
			split_string[j++][k] = '\0';
			k = -1;
		}
	}
	split_string[j++][k] = '\0';

	while (j < COMMAND_LENGTH)
		split_string[j++] = NULL;

	return split_string;
}

// ALGORITHM AUXILIARY
bool relax(Graph *graph, Node *node0, Node *node1)
{
	Edge *edge = get_edge_by_nodes(graph, node0, node1);

	if ((get_node_weight(node0) + get_edge_weight(edge)) < get_node_weight(node1))
	{
		set_node_weight(node1, get_node_weight(node0) + get_edge_weight(edge));
		set_path(node1, node0);
		return true;
	}

	return false;
}

Node** search_path(Graph *graph, Node *start, Node *end)
{
	size_t i, j, nodes_qtt = get_nodes_quantities(graph);
	Node *node = end;
	Node **path = (Node**)malloc((nodes_qtt + 1) * sizeof(Node*));

	path[0] = end;

	for (i = 1; node != NULL; i++, node = get_path(node))
		path[i] = get_path(node);

	path[i] = NULL;

	for (nodes_qtt = 0; path[nodes_qtt] != NULL; nodes_qtt++);

	for (i = 0; i < (nodes_qtt / 2); i++)
	{
		node = path[i];
		path[i] = path[nodes_qtt - 1 - i];
		path[nodes_qtt - 1 - i] = node;
	}

	return path;
}

void print_path(Node **path)
{
	float cost = 0;
	size_t i;

	for (i = 0; path[i] != NULL; i++);
	cost = get_node_weight(path[i - 1]);

	if (isinf(cost))
	{
		printf("Cost: %.2f \n"
			"You don't have any path!\n");
		return;
	}

	printf("Cost: %.2f \n"
		"Path: ", cost);

	for (size_t i = 0; path[i] != NULL; i++)
		printf("%s ", get_node_key(path[i]));

	printf("\n");
}

void reset_shortest_path(Graph *graph)
{
	size_t nodes_qtt = get_nodes_quantities(graph);
	Node **nodes = get_nodes(graph);

	for (size_t i = 0; i < nodes_qtt; i++)
	{
		set_node_weight(nodes[i], INFINITY);
		set_path(nodes[i], NULL);
	}
}

// ALGORITHM
void print_shortest_path(Graph *graph, char *start_node_key, char *end_node_key)
{
	int edges_qtt = get_edges_quantities(graph), nodes_qtt = get_nodes_quantities(graph);
	Node **intersected, *start = get_node(graph, start_node_key), *end = get_node(graph, end_node_key);
	Edge **edges = get_edges(graph);

	set_node_weight(start, 0);

	for (size_t j = 0; j < nodes_qtt - 1; j++)
		for (size_t i = 0; i < edges_qtt; i++)
		{
			intersected = get_intersected_nodes(edges[i]);
			relax(graph, intersected[0], intersected[1]);
			relax(graph, intersected[1], intersected[0]);
		}

	for (size_t i = 0; i < edges_qtt; i++)
	{
		intersected = get_intersected_nodes(edges[i]);
		if (relax(graph, intersected[0], intersected[1]) ||
			relax(graph, intersected[0], intersected[1]))
			printf("Invalid Shortest Path! \n");
	}

	Node **path = search_path(graph, start, end);
	print_path(path);
	free(path);
	path = NULL;
}

// DEFAULT
void organize_nodes_and_edges(Graph *graph)
{
	Node *node = NULL, *node0 = NULL, *node1 = NULL, **nodes = get_nodes(graph);
	Edge *edge = NULL, **edges = get_edges(graph);
	size_t nodes_qtt = get_nodes_quantities(graph), edges_qtt = get_edges_quantities(graph);

	for (size_t i = 0; i < (nodes_qtt / 2); i++)
		for (size_t j = 0; j < nodes_qtt - 1; j++)
			if (strcmp(get_node_key(nodes[j]), get_node_key(nodes[j + 1])) > 0)
			{
				node = nodes[j + 1];
				nodes[j + 1] = nodes[j];
				nodes[j] = node;
			}

	for (size_t i = 0; i < (edges_qtt / 2); i++)
		for (size_t j = 0; j < edges_qtt - 1; j++)
			if (strcmp(get_edge_key(edges[j]), get_edge_key(edges[j + 1])) > 0)
			{
				edge = edges[j + 1];
				edges[j + 1] = edges[j];
				edges[j] = edge;
			}
}

void print_graph(Graph *graph)
{
	Edge **edges = get_edges(graph);
	Node **nodes = get_nodes(graph);

	organize_nodes_and_edges(graph);

	printf("Nodes Quantities: %d \n", get_nodes_quantities(graph));
	for (size_t i = 0, nodes_qtt = get_nodes_quantities(graph); i < nodes_qtt; i++)
		printf("%s ", get_node_key(nodes[i]));

	printf("\nEdges Quantities: %d \n", get_edges_quantities(graph));
	for (size_t i = 0, edges_qtt = get_edges_quantities(graph); i < edges_qtt; i++)
		printf("%s %s %s %.2f \n", get_edge_key(edges[i]),
			get_node_key(get_intersected_nodes(edges[i])[0]),
			get_node_key(get_intersected_nodes(edges[i])[1]),
			get_edge_weight(edges[i]));
}

bool select_option(Graph *graph, char *command)
{
	Node *node = NULL;
	Edge *edge = NULL;
	char **parameters = split(command, ' ');

	// Leu uma linha sem nada, então apenas continua a leitura sem erros.
	if (equals(command, ""))
		return true;

	if (equals(parameters[0], "CV"))
	{
		/*
		CV v
		Cria um vértice com o identificador v
		*/

		if (node_already_exist_by_key(graph, parameters[1]))
			printf("Command: %s - Node already exist! \n", command);
		else
		{
			char *key = (char*)malloc((strlen(parameters[1]) + 1) * sizeof(char));
			strcpy(key, parameters[1]);

			node = create_node(key);
			if (node == NULL)
			{
				printf("Command: %s - create_node fails! \n", command);
				free(key);
			}
			else
			{
				add_node(graph, node);
				printf("Node added! (%s) \n", parameters[1]);
			}
		}
	}
	else if (equals(parameters[0], "RV"))
	{
		/*
		RV v
		Remove o vértice identificado por v
		*/

		if (!node_already_exist_by_key(graph, parameters[1]))
			printf("Command: %s - Node doesn't exist! \n", command);
		else
		{
			remove_node_by_key(graph, parameters[1]);
			printf("Node removed! (%s) \n", parameters[1]);
		}
	}
	else if (equals(parameters[0], "CA"))
	{
		/*
		CA a v1 v2 x
		Cria uma aresta com o identificador a incidindo nos vértices de identificadores v1 e v2.O
		valor armazenado na aresta é um número inteiro especificado por x
		*/
		if (edge_already_exist_by_key(graph, parameters[1]))
			printf("Command: %s - Edge already exist! \n", command);
		else if (!node_already_exist_by_key(graph, parameters[2]) || !node_already_exist_by_key(graph, parameters[3]))
			printf("Command: %s - Some of the nodes doesn't exist! \n", command);
		else
		{
			char *key = (char*)malloc((strlen(parameters[1]) + 1) * sizeof(char));
			strcpy(key, parameters[1]);

			if (is_directed(graph) || strcmp(parameters[2], parameters[3]) <= 0)
				edge = create_edge(key, get_node(graph, parameters[2]),
					get_node(graph, parameters[3]), (float)atoi(parameters[4]));
			else
				edge = create_edge(key, get_node(graph, parameters[3]),
					get_node(graph, parameters[2]), (float)atoi(parameters[4]));

			if (edge == NULL)
			{
				printf("Command: %s - create_edge fails! \n", command);
				free(key);
			}
			else
			{
				add_edge(graph, edge);
				printf("Edge added (%s) \n", parameters[1]);
			}
		}
	}
	else if (equals(parameters[0], "RA"))
	{
		/*
		RA a
		Remove a aresta identificada por a
		*/

		if (!edge_already_exist_by_key(graph, parameters[1]))
			printf("Command: %s - Edge doesn't exist! \n", command);
		else
		{
			remove_edge_by_key(graph, parameters[1]);
			printf("Edge removed! (%s) \n", parameters[1]);
		}
	}
	else if (equals(parameters[0], "TA"))
	{
		/*
		TA a x
		Troca o valor armazenado na aresta de identificador a pelo valor x
		*/

		if (!edge_already_exist_by_key(graph, parameters[1]))
			printf("Command: %s - Edge doesn't exist! \n", command);
		else
		{
			edge = get_edge_by_key(graph, parameters[1]);
			set_edge_weight(edge, (float)atoi(parameters[2]));
			printf("Edge edited! (%s) \n", parameters[1]);
		}
	}
	else if (equals(parameters[0], "IG"))
	{
		/*
		IG
		imprime o grafo na tela. Para definir a forma que seu programa deve imprimir o grafo na
		tela, considere um grafo com n vértices, m arestas, identificadores de vértices v1, v2, ...,
		vn, identificadores de arestas a1, a2, ..., am com respectivos valores x1, x2, ..., xm. Assuma
		ainda que ui e wi representam os identificadores dos vértices em que a aresta ai incide,
		sendo extraídos do conjunto {v1, ..., vn}. A saída do comando deve ser a seguinte:
		Qtd de vértices: n
		v1 v2 ... vn
		Qtd de arestas: m
		a1 u1 w1 x1
		a2 u2 w2 x2
		...
		am um wm xm
		Os identificadores de vértices devem ser impressos em ordem crescente: v1 < v2 < ... < vn
		Os identificadores de arestas devem ser impressos em ordem crescente: a1 < a2 < ... < am
		Os identificadores de vértices em que a aresta ai incide devem ser impressos em ordem
		crescente: ui < wi
		*/
		print_graph(graph);
	}
	else if (equals(parameters[0], "CM"))
	{
		/*
		CM v1 v2
		Determina e imprime o caminho mínimo entre o vértice de identificador v1 e o vértice de
		identificador v2. A saída do comando deve ser a seguinte:
		Custo: c
		Caminho: v1 ... vi vj ... v2
		*/

		if (!node_already_exist_by_key(graph, parameters[1]) || !node_already_exist_by_key(graph, parameters[2]))
			printf("Command: %s - Some of the Nodes doesn't exist! \n", command);
		else
		{
			print_shortest_path(graph, parameters[1], parameters[2]);
			reset_shortest_path(graph);
		}
	}
	else if (equals(parameters[0], "FM"))
	{
		/*
		FM
		Termina a execução do seu programa. Todas as estruturas dinâmicas devem ser
		desalocadas e seu programa deve encerrar
		*/
		destroy_graph(&graph);
		printf("Thank You, Murilo! Please, give me 100 :) \n");
		return false;
	}
	else if (equals(parameters[0], "cls"))
		system("cls");
	else
		printf("Command: %s - Wrong Command. Try Again! \n", command);

	return true;
}

void read_file(Graph *graph)
{
	FILE *file = fopen("commands.txt", "r");
	char read[1000];

	for (size_t i = 1; fgets(read, sizeof read, file); i++)
	{
		read[strlen(read) - 1] = (read[strlen(read) - 1] == '\n' ? '\0' : read[strlen(read) - 1]);

		if (!select_option(graph, read))
			printf("Error! File Line: %d. \n\n", i);
	}
	printf("File Readed! \n");
}

void print_avaliable_commands()
{
	printf("Avaliable Commands \n"

		"CV - Create Node \n"
		"\t - Parameters: node name. \n"

		"RV - Remove Node \n"
		"\t - Parameters: node name. \n"

		"CA - Create Edge \n"
		"\t - Parameters: node1 name, node2 name, edge weight. \n"

		"RA - Remove Edge \n"
		"\t - Parameters: edge name. \n"

		"TA - Change Edge Weight\n"
		"\t - Parameters: edge name, new weight. \n"

		"IG - Print the Graph\n"

		"CM - Print the Shortest Path between two nodes \n"
		"\t - Parameters: node1 name, node2 name. \n"

		"FM - Finish the Program \n"
	);
	getch();
	system("cls");
}

// MAIN
void start_console()
{
	Graph *graph = create_graph(true, false);
	char *command = (char*)malloc(DEFAULT_INPUT_SIZE * sizeof(char));
	char **parameters = NULL;
	command[0] = '\0';

	while (true)
	{
		printf(">> ");
		fgets(command, DEFAULT_INPUT_SIZE, stdin);
		command[strlen(command) - 1] = '\0';

		parameters = split(command, ' ');

		if (equals(parameters[0], "HELP"))
			print_avaliable_commands();
		else if (equals(parameters[0], "READFILE"))
			read_file(graph);
		else if (!select_option(graph, command))
			break;
	}
}
