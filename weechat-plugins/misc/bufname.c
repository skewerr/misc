#include <stdlib.h>

#include "weechat-plugin.h"
#include "misc.h"
#include "bufname.h"

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
