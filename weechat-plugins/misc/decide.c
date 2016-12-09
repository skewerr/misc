/* decide.c
 *
 * Contains functions responsible for the /decide command, most important of
 * which is the command callback, `command_decide_cb`.
 */

#include <stdlib.h>
#include <string.h>

#include "weechat-plugin.h"
#include "misc.h"
#include "decide.h"

#define LEN(A) (sizeof(A)/sizeof(A[0]))

/* proto */
static const char *choose_delim(void);
static int compile_list(const char **);

static char *c_duplicate; /* global variable => NULL */
static char *c_token;     /* global variable => NULL */
static char *c_result;    /* global variable => NULL */

static const char *c_fallback[] = {
	"yes",
	"maybe",
	"no"
};

static const char *c_delim[] = {
	"|",
	" or ",
	", "
};

int
command_decide_cb(const void *pointer, void *data,
	struct t_gui_buffer *buffer,
	int argc, char **argv, char **argv_eol)
{
	const char *c_array[argc - 1];
	int c_num;

	if (argc == 1)
	{
		weechat_printf(NULL, "%sArguments needed!",
			weechat_prefix("error"));

		return WEECHAT_RC_ERROR;
	}

	c_duplicate = strdup(argv_eol[1]);
	c_num       = compile_list(c_array);

	c_result = weechat_string_strip(((c_num > 1) ?
		c_array[rand() % c_num] :
		c_fallback[rand() % LEN(c_fallback)]),
		1, 1, " ");

	weechat_buffer_set(buffer, "input", c_result);

	free(c_duplicate); free(c_result);
	c_result = c_duplicate = NULL;

	return WEECHAT_RC_OK;
}

static const char *
choose_delim(void)
{
	const char *needle = NULL;
	int i;

	for (i = 0; i < LEN(c_delim); ++i)
	{
		if ((needle = strstr(c_duplicate, c_delim[i])) != NULL &&
			*(needle + strlen(c_delim[i])) != '\0')
			return c_delim[i];
	}

	return NULL;
}

static int
compile_list(const char **list)
{
	const char *haystack = c_duplicate;
	const char *delim = NULL;
	char *needle = NULL;
	int delim_length;
	int count = 1;

	list[0] = c_duplicate;

	if ((delim = choose_delim()) == NULL)
		return 1;

	delim_length = strlen(delim);

	while((needle = strstr(haystack, delim)) != NULL)
	{
		*needle = '\0';
		haystack = needle + delim_length;
		list[count++] = haystack;
	}

	return count;
}
