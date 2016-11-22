#include <stdio.h>
#include <stdlib.h>

#include "bfops.h"

FILE *fstream;

int
main(int argc, char **argv)
{
	char c;

	if (argc != 2 || (fstream = fopen(argv[1], "r")) == NULL)
	{
		printf("Couldn't open file or didn't get a filename.\n");
		exit(EXIT_FAILURE);
	}

	init_arrays();

	while ((c = fgetc(fstream)) != EOF)
		interpret(c);

	/* makes little sense to do cleanup here */

	return EXIT_SUCCESS;
}
