#include <stdlib.h>
#include <string.h>

#include "weechat-plugin.h"

#define LEN(A) (sizeof(A)/sizeof(A[0]))

WEECHAT_PLUGIN_NAME       	("misc");
WEECHAT_PLUGIN_DESCRIPTION	("Some useless stuff");
WEECHAT_PLUGIN_AUTHOR     	("Wilson <spoonm@spoonm.org>");
WEECHAT_PLUGIN_VERSION    	("0.1");
WEECHAT_PLUGIN_LICENSE    	("WTFPL");

struct t_weechat_plugin *weechat_plugin = NULL;

/* callback for "/bufname" */

int
command_bufname_cb(const void *pointer, void *data,
	struct t_gui_buffer *buffer,
	int argc, char **argv, char **argv_eol)
{
	if (argc > 1)
	{
		weechat_printf(NULL, "%sThis command takes no arguments.",
			weechat_prefix("error"));

		return WEECHAT_RC_ERROR;
	}

	weechat_buffer_set(buffer, "input",
		weechat_buffer_get_string(buffer, "name"));

	return WEECHAT_RC_OK;
}

/* callback for "/decide" */

int
command_decide_cb(const void *pointer, void *data,
	struct t_gui_buffer *buffer,
	int argc, char **argv, char **argv_eol)
{
	const char *c_fbk[] = {"yes", "no", "maybe"};
	const char *c_arr[argc - 1];
	const char *c_res = NULL;
	char *c_tok = NULL;
	char *c_dup = NULL;
	int c_num = 1;

	if (argc == 1)
	{
		weechat_printf(NULL, "%sArguments needed!",
			weechat_prefix("error"));

		return WEECHAT_RC_ERROR;
	}

	c_dup    = strdup(argv_eol[1]);
	c_arr[0] = strtok(c_dup, "|");

	while((c_tok = strtok(NULL, "| ")) != NULL)
		c_arr[c_num++] = c_tok;

	c_res = (c_num > 1) ? c_arr[rand() % c_num] :
		c_fbk[rand() % LEN(c_fbk)];

	weechat_buffer_set(buffer, "input", c_res);

	free(c_dup);

	return WEECHAT_RC_OK;
}

/* init/end functions */

int
weechat_plugin_init(struct t_weechat_plugin *plugin,
	int argc, char **argv)
{
	weechat_plugin = plugin;

	weechat_hook_command("bufname",
		"display the name of the current buffer in the input line",
		NULL, NULL, NULL, &command_bufname_cb, NULL, NULL);

	weechat_hook_command("decide",
		"make a random decision using stdlib's rand()",
		"op1 | op2 | ...", NULL, NULL, &command_decide_cb, NULL, NULL);

	return WEECHAT_RC_OK;
}

int
weechat_plugin_end(struct t_weechat_plugin *plugin)
{
	return WEECHAT_RC_OK;
}
