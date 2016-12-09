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

static char *c_duplicate; /* global variable => NULL */
static char *c_token;     /* global variable => NULL */
static char *c_result;    /* global variable => NULL */

static const char *c_fallback[] = {
	"yes",
	"maybe",
	"no"
};

int
command_decide_cb(const void *pointer, void *data,
	struct t_gui_buffer *buffer,
	int argc, char **argv, char **argv_eol)
{
	const char *c_array[argc - 1];
	int c_num = 1;

	if (argc == 1)
	{
		weechat_printf(NULL, "%sArguments needed!",
			weechat_prefix("error"));

		return WEECHAT_RC_ERROR;
	}

	c_duplicate = strdup(argv_eol[1]);
	c_array[0]  = strtok(c_duplicate, "|");

	while((c_token = strtok(NULL, "|")) != NULL)
		c_array[c_num++] = c_token;

	c_result = weechat_string_strip(((c_num > 1) ?
		c_array[rand() % c_num] :
		c_fallback[rand() % LEN(c_fallback)]),
		1, 1, " ");

	weechat_buffer_set(buffer, "input", c_result);

	free(c_duplicate); free(c_result);
	c_result = c_duplicate = NULL;

	return WEECHAT_RC_OK;
}
