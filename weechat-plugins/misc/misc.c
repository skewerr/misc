#include <stdlib.h>
#include <string.h>

#include "weechat-plugin.h"
#include "misc.h"

#include "decide.h"
#include "bufname.h"

WEECHAT_PLUGIN_NAME       	("misc");
WEECHAT_PLUGIN_DESCRIPTION	("Some useless stuff");
WEECHAT_PLUGIN_AUTHOR     	("Wilson <spoonm@spoonm.org>");
WEECHAT_PLUGIN_VERSION    	("0.1");
WEECHAT_PLUGIN_LICENSE    	("WTFPL");

struct t_weechat_plugin *weechat_plugin = NULL;

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
