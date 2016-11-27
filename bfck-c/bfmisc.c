#include <stdio.h>
#include <unistd.h>

#include "bfmisc.h"
#include "bfops.h"

void print_output(char op)
{
	int offset = curr_pnt - cell_arr;
	int i;

	printf("\033[1;1H"); /* return to the first terminal cell */

	printf(" Cell #:");

	for (i = -4; i < 5; i++)
		printf("\t%3d", offset + i);

	putchar('\n');

	printf(" Cell V:");

	for (i = -4; i < 5; i++)
		printf("\t%3d", (offset + i >= 0) ? *(cell_arr + offset + i) : 0);

	putchar('\n');

	printf("Pointer:\t   \t   \t   \t   \t  ^\n");
	printf("   Oper: %c\n", op);
	printf(" Output: %s\n", out_str);

	usleep(30000); /* obsolete, but the alternative is ugly, ngl */
}
