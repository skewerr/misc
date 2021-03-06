#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

const char *FILENAME = "/home/spoonm/.local/share/todo/todolist";
const char *FILECOPY = "/home/spoonm/.local/share/todo/.todolist.tmp";

FILE *fp; /* global means these start as NULL */
FILE *cp;

void
todo_addline(const char *line)
{
	fp = fopen(FILENAME, "a");

	fputs(line, fp);
	fputc('\n', fp);

	fclose(fp); fp = NULL;
}

void
todo_delline(const char *index)
{
	char buf[512];
	int i, j;

	fp = fopen(FILENAME, "r");
	cp = fopen(FILECOPY, "w");
	i = atoi(index);

	for (j = 0; fgets(buf, sizeof buf, fp); ++j)
	{
		if (j != i)
			fputs(buf, cp);
	}

	fclose(fp); fp = NULL;
	fclose(cp); cp = NULL;

	rename(FILECOPY, FILENAME);
}

void
todo_repline(const char *index, const char *line)
{
	char buf[512];
	int i, j;

	fp = fopen(FILENAME, "r");
	cp = fopen(FILECOPY, "w");
	i = atoi(index);

	for (j = 0; fgets(buf, sizeof buf, fp); ++j)
	{
		if (j != i) {
			fputs(buf, cp);
		} else {
			fputs(line, cp);
			fputc('\n', cp);
		}
	}

	fclose(fp); fp = NULL;
	fclose(cp); cp = NULL;

	rename(FILECOPY, FILENAME);

}

void
todo_list(void)
{
	char buf[512];
	int i;

	fp = fopen(FILENAME, "r");

	for (i = 0; fgets(buf, sizeof buf, fp); ++i)
		printf("%d %s", i, buf);

	fclose(fp); fp = NULL;
}

int
main(int argc, char **argv)
{
	const char *repind = NULL;
	int op;

	switch ((op = getopt(argc, argv, "a:d:r:l")))
	{
		case 'a': todo_addline(optarg); todo_list(); break;
		case 'd': todo_delline(optarg); todo_list(); break;
		case 'l': todo_list();                       break;
		case 'r': repind = optarg;                   break;
		case  -1: system("todo.sh");                 break;

		case '?': return 1;
		default:  abort();
	}

	if (repind != NULL) {
		todo_repline(repind, argv[optind]);
		todo_list();
	}

	return 0;
}
