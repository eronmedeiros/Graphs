#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Graph.h"
#include "Node.h"
#include "Edge.h"

#define DEFAULT_STRING_SIZE 50

void test()
{
	Graph *graph = create_graph(1);

	Node *node_a = create_node('a');
	Node *node_b = create_node('b');
	Node *node_c = create_node('c');
	Node *node_d = create_node('d');
	Node *node_e = create_node('e');
	Node *node_f = create_node('f');
	Node *node_g = create_node('g');
	Node *node_h = create_node('h');
	Node *node_i = create_node('i');
	Node *node_j = create_node('j');
	Node *node_k = create_node('k');
	Node *node_l = create_node('l');
	Node *node_m = create_node('m');
	Node *node_n = create_node('n');

	Edge *edge_a_e = create_edge('A', node_a, node_e, 5);
	Edge *edge_a_f = create_edge('B', node_a, node_f, 1);
	Edge *edge_a_n = create_edge('C', node_a, node_l, 2);
	Edge *edge_b_c = create_edge('D', node_b, node_c, 11);
	Edge *edge_b_e = create_edge('E', node_b, node_e, 1);
	Edge *edge_b_i = create_edge('F', node_b, node_i, 9);
	Edge *edge_c_d = create_edge('G', node_c, node_d, 3);
	Edge *edge_c_f = create_edge('H', node_c, node_f, 3);
	Edge *edge_c_g = create_edge('I', node_c, node_g, 5);
	Edge *edge_c_j = create_edge('J', node_c, node_j, 6);
	Edge *edge_d_g = create_edge('K', node_d, node_g, 4);
	Edge *edge_d_n = create_edge('L', node_d, node_n, 5);
	Edge *edge_e_h = create_edge('M', node_e, node_h, 8);
	Edge *edge_f_g = create_edge('N', node_f, node_g, 1);
	Edge *edge_f_i = create_edge('O', node_f, node_i, 6);
	Edge *edge_f_m = create_edge('P', node_f, node_m, 4);
	Edge *edge_h_i = create_edge('Q', node_h, node_i, 10);
	Edge *edge_h_m = create_edge('R', node_h, node_m, 7);
	Edge *edge_j_k = create_edge('S', node_j, node_k, 13);
	Edge *edge_j_l = create_edge('T', node_j, node_l, 8);
	Edge *edge_k_m = create_edge('U', node_k, node_m, 9);
	Edge *edge_k_n = create_edge('V', node_k, node_n, 6);

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

	print_shortest_path(graph, 'a', 'n');

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
			k = -1;
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
	char *command = (char*) malloc(DEFAULT_STRING_SIZE * sizeof(char));

	while (true)
	{
		printf("\n>> ");
		fgets(command, sizeof command, stdin);

		parameters = split(command);

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
				node = create_node(parameters[1]);
				add_node(graph, node);
				printf("Node added! \n");
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
			else if (!node_already_exist(graph, parameters[2]) || !node_already_exist(graph, parameters[3]))
				printf("Some of the nodes doesn't exist! \n");
			else
			{
				edge = create_edge(parameters[1], get_node(graph, parameters[2]),
					get_node(graph, parameters[3]), (float)atoi(parameters[4]));
				add_edge(graph, edge);
				printf("Edge added \n");
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
			graph_status(graph);
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

			if (!node_already_exist_by_key(graph, parameters[1]) || !node_already_exist(graph, parameters[2]))
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
			destroy_edge(&edge);
			destroy_node(&node);
			destroy_graph(&graph);
			break;
		}
		else if (equals(parameters[0], "CGS")) // check graph status
		{
			graph_status(graph);
		}
		else
			printf("Wrong Command. Try Again! \n");
		
		getch();
	}
	
	printf("Programa Finalizado! \n");
}

void menu()
{
	size_t option = 0;
	Graph *graph = NULL;
	Node *node = NULL;
	Edge *edge = NULL;

	while (true)
	{
		printf(
			"1 - Create Node \n"
			"2 - Remove Node \n"
			"3 - Create Edge \n"
			"4 - Remove Edge \n"
			"5 - Edit Edge \n"
			"6 - Print Graph \n"
			"7 - Shortest Way \n"
			"8 - Exit Program \n"
			">> ");

		scanf("%d", &option);
		fflush(stdin);

		while (option > 8 || option < 1)
		{
			printf("Invalid Option! \n>>");
			scanf("%d", &option);
			fflush(stdin);
		}

		switch (option)
		{
			case 1:
				menu_create_node(graph);
				break;
			case 2:
				menu_remove_node(graph);
				break;
			case 3:
				menu_create_edge(graph);
				break;
			case 4:
				menu_remove_edge(graph);
				break;
			case 5:
				menu_edit_edge(graph);
				break;
			case 6:
				menu_print_graph(graph);
				break;
			case 7:
				menu_shortest_way(graph);
				break;
			case 8:
				menu_exit(graph);
				break;
			default:
				printf("FAIL! (switch_menu)");
				break;
		}

	}
}

void read_file()
{

}

bool equals(char *str1, char *str2)
{
	return !strcmp(str1, str2) ? true : false;
}

//
//void menu_create_node(graph)
//{
//	char *node_key = (char*) malloc(8 * sizeof(char));
//	
//	printf("Node Key: \n>>");
//	fgets(node_key, sizeof node_key, stdin);
//
//	add_node(graph, create_node(node_key));
//}
//
//menu_remove_node(graph);
//menu_create_edge(graph);
//menu_remove_edge(graph);
//menu_edit_edge(graph);
//menu_print_graph(graph);
//menu_shortest_way(graph);
//menu_exit(graph);