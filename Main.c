#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "Trabalho.h"

int main()
{
	int option;

	printf(
		"0 - Start Console \n"
		"1 - Read File \n");

	scanf("%d", &option);

	if (option)
		start_console();
	else
		read_file();

	getch();

    return 0;
}
