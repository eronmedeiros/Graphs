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

	Node *node1 = create_node(1);
	Node *node2 = create_node(2);
	Node *node3 = create_node(3);
	Node *node4 = create_node(4);
	Node *node5 = create_node(5);
	Node *node6 = create_node(6);
	Node *node7 = create_node(7);
	Node *node8 = create_node(8);
	Node *node9 = create_node(9);
	Node *node10 = create_node(10);
	Node *node11 = create_node(11);
	Node *node12 = create_node(12);
	Node *node13 = create_node(13);
	Node *node14 = create_node(14);

	Edge *edge1_5 = create_edge(101, node1, node5, 5);
	Edge *edge1_6 = create_edge(102, node1, node6, 1);
	Edge *edge1_12 = create_edge(103, node1, node12, 2);
	Edge *edge2_3 = create_edge(104, node2, node3, 11);
	Edge *edge2_5 = create_edge(105, node2, node5, 1);
	Edge *edge2_9 = create_edge(106, node2, node9, 9);
	Edge *edge3_4 = create_edge(107, node3, node4, 3);
	Edge *edge3_6 = create_edge(108, node3, node6, 3);
	Edge *edge3_7 = create_edge(109, node3, node7, 5);
	Edge *edge3_10 = create_edge(110, node3, node10, 6);
	Edge *edge4_7 = create_edge(111, node4, node7, 4);
	Edge *edge4_14 = create_edge(112, node4, node14, 5);
	Edge *edge5_8 = create_edge(113, node5, node8, 8);
	Edge *edge6_7 = create_edge(114, node6, node7, 1);
	Edge *edge6_9 = create_edge(115, node6, node9, 6);
	Edge *edge6_13 = create_edge(116, node6, node13, 4);
	Edge *edge8_9 = create_edge(117, node8, node9, 10);
	Edge *edge8_13 = create_edge(118, node8, node13, 7);
	Edge *edge10_11 = create_edge(119, node10, node11, 13);
	Edge *edge10_12 = create_edge(120, node10, node12, 8);
	Edge *edge11_13 = create_edge(121, node11, node13, 9);
	Edge *edge11_14 = create_edge(122, node11, node14, 6);

	add_node(graph, node1);
	add_node(graph, node2);
	add_node(graph, node3);
	add_node(graph, node4);
	add_node(graph, node5);
	add_node(graph, node6);
	add_node(graph, node7);
	add_node(graph, node8);
	add_node(graph, node9);
	add_node(graph, node10);
	add_node(graph, node11);
	add_node(graph, node12);
	add_node(graph, node13);
	add_node(graph, node14);

	add_edge(graph, edge1_5);
	add_edge(graph, edge1_6);
	add_edge(graph, edge1_12);
	add_edge(graph, edge2_3);
	add_edge(graph, edge2_5);
	add_edge(graph, edge2_9);
	add_edge(graph, edge3_4);
	add_edge(graph, edge3_6);
	add_edge(graph, edge3_7);
	add_edge(graph, edge3_10);
	add_edge(graph, edge4_7);
	add_edge(graph, edge4_14);
	add_edge(graph, edge5_8);
	add_edge(graph, edge6_7);
	add_edge(graph, edge6_9);
	add_edge(graph, edge6_13);
	add_edge(graph, edge8_9);
	add_edge(graph, edge8_13);
	add_edge(graph, edge10_11);
	add_edge(graph, edge10_12);
	add_edge(graph, edge11_13);
	add_edge(graph, edge11_14);

	//graph_status(graph);

	printf("-------------------------------------------- \n");

	print_shortest_path(graph, 1, 14);

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
								(float) atoi(parameters[4]));

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
			set_edge_weight(edge, (float) atoi(parameters[2]));
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
			print_shortest_path(graph, atoi(parameters[1]), atoi(parameters[2]));
		}
		else if (!strcmp(parameters[0], "FM"))
		{
			/*
			FM
			Termina a execução do seu programa. Todas as estruturas dinâmicas devem ser
			desalocadas e seu programa deve encerrar
			*/
			destroy_edge(&edge);
			destroy_node(&node);
			destroy_graph(&graph);
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
