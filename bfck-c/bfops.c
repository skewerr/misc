#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "bfops.h"
#include "bfmisc.h"

long  	*loop_arr;
size_t	loop_iter;
size_t	loop_cnt;

uint8_t	*cell_arr;
uint8_t	*curr_pnt;
size_t 	cell_cnt;

char  	out_str[512];
size_t	out_iter;

void
init_arrays(void)
{
	/* TODO: memory tests */
	cell_arr = calloc(10, 1);
	loop_arr = malloc(5 * sizeof(long));

	curr_pnt = cell_arr;
	cell_cnt = 10;
	loop_cnt = 5;

	memset(out_str, 0, 512);
}

void
interpret(const char op)
{
	int offset;
	int i;

	switch (op)
	{
		case '+': inc_cell();  	break;
		case '-': dec_cell();  	break;
		case '>': inc_pntr();  	break;
		case '<': dec_pntr();  	break;
		case '[': start_loop();	break;
		case ']': end_loop();  	break;
		case '.': print_char();	break;
		case ',': read_char(); 	break;

		default:
			return;
	}

	print_output(op);
}

/* character IO */

void
read_char(void)
{
	int c;

	if ((c = fgetc(stdin)) == EOF)
	{
		printf("EOF found on stdin. (Exiting...)\n");
		exit(EXIT_SUCCESS);
	}
	else
		*curr_pnt = c;
}

void
print_char(void)
{
	out_str[out_iter++] = *curr_pnt;
}

/* loop magic */

void
start_loop(void)
{
	if (loop_iter == loop_cnt - 1)
	{
		/* TODO: memory tests */
		loop_cnt += 5;
		loop_arr = realloc(loop_arr, loop_cnt * sizeof(long));
	}

	*(loop_arr + loop_iter++) = ftell(fstream);
}

void
end_loop(void)
{
	if (*curr_pnt)
		fseek(fstream, *(loop_arr + loop_iter-1), SEEK_SET);
	else if (loop_iter)
		loop_iter--;
	else
	{
		printf("[ERROR] Attempt to end unstarted loop.\n");
		exit(EXIT_FAILURE);
	}
}

/* cell arithmetic */

void
inc_cell(void)
{
	(*curr_pnt)++;
}

void
dec_cell(void)
{
	(*curr_pnt)--;
}

/* pointer mangling */

void
inc_pntr(void)
{
	if ((curr_pnt - cell_arr) == cell_cnt - 4)
	{
		/* TODO: memory tests */
		cell_cnt += 8;
		cell_arr = realloc(cell_arr, cell_cnt);
		curr_pnt = cell_arr + cell_cnt - 6;

		memset(curr_pnt + 1, 0, 8);
	}

	curr_pnt++;
}

void
dec_pntr(void)
{
	if (curr_pnt - cell_arr)
		curr_pnt--;
	else
	{
		printf("[ERROR] Attempt to go to cell #-1\n");
		exit(EXIT_FAILURE);
	}
}
