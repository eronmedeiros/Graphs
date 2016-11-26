#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Graph.h"
#include "Node.h"
#include "Edge.h"

#define DEFAULT_INPUT_SIZE 50
#define COMMAND_LENGTH 6

bool equals(char *str1, char *str2)
{
	return !strcmp(str1, str2) ? true : false;
}

/*
void test()
{
	Graph *graph = create_graph(true, false);

	Node *node_a = create_node("a");
	Node *node_b = create_node("b");
	Node *node_c = create_node("c");
	Node *node_d = create_node("d");
	Node *node_e = create_node("e");
	Node *node_f = create_node("f");
	Node *node_g = create_node("g");
	Node *node_h = create_node("h");
	Node *node_i = create_node("i");
	Node *node_j = create_node("j");
	Node *node_k = create_node("k");
	Node *node_l = create_node("l");
	Node *node_m = create_node("m");
	Node *node_n = create_node("n");

	Edge *edge_a_e = create_edge("A", node_a, node_e, 5);
	Edge *edge_a_f = create_edge("B", node_a, node_f, 1);
	Edge *edge_a_n = create_edge("C", node_a, node_l, 2);
	Edge *edge_b_c = create_edge("D", node_b, node_c, 11);
	Edge *edge_b_e = create_edge("E", node_b, node_e, 1);
	Edge *edge_b_i = create_edge("F", node_b, node_i, 9);
	Edge *edge_c_d = create_edge("G", node_c, node_d, 3);
	Edge *edge_c_f = create_edge("H", node_c, node_f, 3);
	Edge *edge_c_g = create_edge("I", node_c, node_g, 5);
	Edge *edge_c_j = create_edge("J", node_c, node_j, 6);
	Edge *edge_d_g = create_edge("K", node_d, node_g, 4);
	Edge *edge_d_n = create_edge("L", node_d, node_n, 5);
	Edge *edge_e_h = create_edge("M", node_e, node_h, 8);
	Edge *edge_f_g = create_edge("N", node_f, node_g, 1);
	Edge *edge_f_i = create_edge("O", node_f, node_i, 6);
	Edge *edge_f_m = create_edge("P", node_f, node_m, 4);
	Edge *edge_h_i = create_edge("Q", node_h, node_i, 10);
	Edge *edge_h_m = create_edge("R", node_h, node_m, 7);
	Edge *edge_j_k = create_edge("S", node_j, node_k, 13);
	Edge *edge_j_l = create_edge("T", node_j, node_l, 8);
	Edge *edge_k_m = create_edge("U", node_k, node_m, 9);
	Edge *edge_k_n = create_edge("V", node_k, node_n, 6);

	add_node(graph, node_a);
	add_node(graph, node_b);
	add_node(graph, node_c);
	add_node(graph, node_d);
	add_node(graph, node_e);
	add_node(graph, node_f);
	add_node(graph, node_g);
	add_node(graph, node_h);
	add_node(graph, node_i);
	add_node(graph, node_j);
	add_node(graph, node_k);
	add_node(graph, node_l);
	add_node(graph, node_m);
	add_node(graph, node_n);
	
	add_edge(graph, edge_a_e);
	add_edge(graph, edge_a_f);
	add_edge(graph, edge_a_n);
	add_edge(graph, edge_b_c);
	add_edge(graph, edge_b_e);
	add_edge(graph, edge_b_i);
	add_edge(graph, edge_c_d);
	add_edge(graph, edge_c_f);
	add_edge(graph, edge_c_g);
	add_edge(graph, edge_c_j);
	add_edge(graph, edge_d_g);
	add_edge(graph, edge_d_n);
	add_edge(graph, edge_e_h);
	add_edge(graph, edge_f_g);
	add_edge(graph, edge_f_i);
	add_edge(graph, edge_f_m);
	add_edge(graph, edge_h_i);
	add_edge(graph, edge_h_m);
	add_edge(graph, edge_j_k);
	add_edge(graph, edge_j_l);
	add_edge(graph, edge_k_m);
	add_edge(graph, edge_k_n);

	//graph_status(graph);

	printf("-------------------------------------------- \n");

	print_shortest_path(graph, "a", "n");

	printf("-------------------------------------------- \n");

	destroy_graph(&graph);
}
*/

char** split(char *string, char delimiter)
{
	int i, j, k;
	char **split_string = (char **)malloc(COMMAND_LENGTH * sizeof(char*));

	for (i = 0; i < COMMAND_LENGTH; i++)
		split_string[i] = (char *)malloc(strlen(string) * sizeof(char));

	for (i = j = k = 0; string[i] != '\n'; i++, k++)
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

void start_console()
{
	Graph *graph = create_graph(true, false);
	Node *node = NULL;
	Edge *edge = NULL;
	char **parameters = NULL;
	char *command = (char*) malloc(DEFAULT_INPUT_SIZE * sizeof(char));

	while (true)
	{
		printf(">> ");
		fgets(command, DEFAULT_INPUT_SIZE, stdin);

		parameters = split(command, ' ');
		
		if (equals(parameters[0], "CV"))
		{
			/*
			CV v
			Cria um vértice com o identificador v
			*/

			if (node_already_exist_by_key(graph, parameters[1]))
				printf("Node already exist! \n");
			else
			{
				char *key = (char*)malloc((strlen(parameters[1]) + 1) * sizeof(char));
				strcpy(key, parameters[1]);

				node = create_node(key);
				if (node == NULL)
					printf("create_node fails! \n");
				else
				{
					add_node(graph, node);
					printf("Node added! \n");
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
				printf("Node doesn't exist! \n");
			else
			{
				remove_node_by_key(graph, parameters[1]);
				printf("Node removed! \n");
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
				printf("Edge already exist! \n");
			else if (!node_already_exist_by_key(graph, parameters[2]) || !node_already_exist_by_key(graph, parameters[3]))
				printf("Some of the nodes doesn't exist! \n");
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
					printf("create_edge fails! \n");
				else
				{
					add_edge(graph, edge);
					printf("Edge added \n");
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
				printf("Edge doesn't exist! \n");
			else
			{
				remove_edge_by_key(graph, parameters[1]);
				printf("Edge removed! \n");
			}
		}
		else if (equals(parameters[0], "TA"))
		{
			/*
			TA a x
			Troca o valor armazenado na aresta de identificador a pelo valor x
			*/

			if (!edge_already_exist_by_key(graph, parameters[1]))
				printf("Edge doesn't exist! \n");
			else
			{
				edge = get_edge_by_key(graph, parameters[1]);
				set_edge_weight(edge, (float) atoi(parameters[2]));
				printf("Edge edited! \n");
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
			print_formated_graph(graph);
			graph_status2(graph);
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
				printf("Some of the Nodes doesn't exist! \n");
			else
				print_shortest_path(graph, parameters[1], parameters[2]);
		}
		else if (equals(parameters[0], "FM"))
		{
			/*
			FM
			Termina a execução do seu programa. Todas as estruturas dinâmicas devem ser
			desalocadas e seu programa deve encerrar
			*/
			destroy_graph(&graph);
			break;
		}
		else if (equals(parameters[0], "CGS")) // check graph status
		{
			graph_status(graph);
		}
		else
			printf("Wrong Command. Try Again! \n");

		for (size_t i = 0; i < COMMAND_LENGTH; i++)
			free(parameters[i]);

		free(parameters);
	}
	
	printf("Programa Finalizado! \n");
}

void print_formated_graph(Graph *graph)
{
	Edge **edges = get_edges(graph);
	Node **nodes = get_nodes(graph);

	organize_nodes_and_edges(graph);

	printf("Nodes Quantities: %d \n", get_nodes_quantities(graph));
	for (size_t i = 0, nodes_qtt = get_nodes_quantities(graph); i < nodes_qtt; i++)
		printf("%s \n", get_node_key(nodes[i]));

	printf("Edges Quantities: %d \n", get_edges_quantities(graph));
	for (size_t i = 0, edges_qtt = get_edges_qtt(graph); i < edges_qtt; i++)
		printf("%s %s %s %s \n", get_edge_key(edges[i]),
			get_edge_key(get_intersected_nodes(edges[i])[0]),
			get_edge_key(get_intersected_nodes(edges[i])[1]),
			get_edge_weight(edges[i]));
}

void read_file()
{
	FILE *file = fopen("", 'r');
	char read[1000];

	while (file != NULL)
	{
		fgets(read, sizeof read, file);
		
	}
}

void organize_nodes_and_edges(Graph *graph)
{
	Node *node = NULL;
	Edge *edge = NULL;
	Node **nodes = get_nodes(graph);
	Edge **edges = get_edges(graph);
	size_t nodes_qtt = get_nodes_quantities(graph), edges_qtt = get_edges_qtt(graph);

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