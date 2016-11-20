#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Graph.h"
#include "Node.h"
#include "Edge.h"

void test()
{
	Graph *graph = create_graph(1);
	graph_status(graph);

	printf("-------------------------------------------- \n");

	Node *node1 = create_node(1);
	Node *node2 = create_node(2);
	Node *node3 = create_node(3);
	Edge *edge12 = create_edge(1, node1, node2, 10);
	Edge *edge13 = create_edge(2, node1, node3, 10);

	add_node(graph, node1);
	add_node(graph, node2);
	add_node(graph, node3);

	add_edge(graph, edge12);
	add_edge(graph, edge13);

	graph_status(graph);

	printf("-------------------------------------------- \n");

	destroy_graph(&graph);
}

char** split(char *string)
{
	#define ARRAY_LENGHT 5

	char **splitted_string = (char**) malloc(ARRAY_LENGHT * sizeof(char*));
	size_t i, j, k, len = strlen(string);

	for (i = 0; i < ARRAY_LENGHT; i++)
		splitted_string[i] = (char*) malloc(len * sizeof(char));

	for (i = 0, j = 0, k = 0; i < strlen(string); i++, k++)
	{
		if (string[i] != ' ')
			splitted_string[j][k] = string[i];
		else
		{
			splitted_string[j][k] = '\0';
			j++;
			k = 0;
		}	
	}
	while (j < ARRAY_LENGHT)
		splitted_string[j++] = NULL;

	return splitted_string;
}

int string_to_int(char *string)
{
	int int_ = 0;
	int j = 1;

	for (size_t i = strlen(string) - 1; i >= 0; i--, j *= 10)
		int_ += ((string[i] - '0') * j);

	return int_;
}

void start_console()
{
	Graph *graph = create_graph(1);
	Node *node = NULL;
	Edge *edge = NULL;
	char **parameters;
	char *command = (char*) malloc(20 * sizeof(char));

	while (true)
	{
		printf("\n>> ");
		fgets(command, sizeof command, stdin);

		parameters = split(command);

		if (!strcmp(parameters[0], "CV"))
		{
			/*
			CV v
			Cria um vértice com o identificador v
			*/

			node = create_node(atoi(parameters[1]));
			add_node(graph, node);
		}
		else if (!strcmp(parameters[0], "RV"))
		{
			/*
			RV v
			Remove o vértice identificado por v
			*/

			remove_node_by_key(graph, atoi(parameters[1]));
		}
		else if (!strcmp(parameters[0], "CA"))
		{
			/*
			CA a v1 v2 x
			Cria uma aresta com o identificador a incidindo nos vértices de identificadores v1 e v2.O
			valor armazenado na aresta é um número inteiro especificado por x
			*/
			edge = create_edge (atoi(parameters[1]),
								get_node(graph, atoi(parameters[2])),
								get_node(graph, atoi(parameters[3])),
								(float)atoi(parameters[4]));

			add_edge(graph, edge);
		}
		else if (!strcmp(parameters[0], "RA"))
		{
			/*
			RA a
			Remove a aresta identificada por a
			*/
			remove_edge_by_key(graph, atoi(parameters[1]));
		}
		else if (!strcmp(parameters[0], "TA"))
		{
			/*
			TA a x
			Troca o valor armazenado na aresta de identificador a pelo valor x
			*/
			edge = get_edge_by_key(graph, atoi(parameters[1]));
			set_edge_weight(edge, atoi(parameters[2]));
		}
		else if (!strcmp(parameters[0], "IG"))
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
			graph_status(graph);
		}
		else if (!strcmp(parameters[0], "CM"))
		{
			/*
			CM v1 v2
			Determina e imprime o caminho mínimo entre o vértice de identificador v1 e o vértice de
			identificador v2. A saída do comando deve ser a seguinte:
			Custo: c
			Caminho: v1 ... vi vj ... v2
			*/
			Edge** path = shortest_path(graph, atoi(parameters[1]), atoi(parameters[2]));

			for (size_t i = 0; path[i] != NULL; i++)
				printf("%d ", get_edge_key(path[i]));

			free(path);
		}
		else if (!strcmp(parameters[0], "FM"))
		{
			/*
			FM
			Termina a execução do seu programa. Todas as estruturas dinâmicas devem ser
			desalocadas e seu programa deve encerrar
			*/
			destroy_edge(edge);
			destroy_node(node);
			destroy_graph(graph);
			break;
		}
		else if (!strcmp(parameters[0], "CGS")) // check graph status
		{
			graph_status(graph);
		}
		else
			printf("Wrong Command. Try Again! \n");
		
		getch();
	}
	
	printf("Programa Finalizado! \n");
}
