# -*- coding: utf-8 -*-
#
# LICENSE bit: do whatever the fuck you want with it, I don't care.

SCRIPT_NAME   	= "misc_stuff"
SCRIPT_AUTHOR 	= "Wilson <spoonm@spoonm.org>"
SCRIPT_VERSION	= "0.1"
SCRIPT_LICENSE	= "WTFPL"
SCRIPT_DESC   	= "Tricks and dirty hacks."

import_ok = True

try:
	import weechat
	import random
except ImportError:
	print("This script must be run from within weechat.")
	import_ok = False

def bufname(data, buffer, args):

	"""
	Display buffer name in the input bar.
	Only useful in my personal setup.
	"""

	b = weechat.current_buffer()
	bname = weechat.buffer_get_string(b, "name")

	weechat.buffer_set(b, "input", bname)

	return weechat.WEECHAT_RC_OK

def decide(data, buffer, args):

	"""
	Make a random decision from a list.
	"""

	optuple = ("|", " or ")
	choicelist = [args]

	for op in optuple:
		if op in args:
			choicelist = [c for c in args.split(op) if c]
			break

	if len(choicelist) <= 1:
		choicelist = ["yes", "no", "maybe"]

	weechat.buffer_set(buffer, "input", random.choice(choicelist))

	return weechat.WEECHAT_RC_OK

if __name__ == "__main__" and import_ok:

	weechat.register(
		SCRIPT_NAME,
		SCRIPT_AUTHOR,
		SCRIPT_VERSION,
		SCRIPT_LICENSE,
		SCRIPT_DESC, "", "")

	weechat.hook_command("bufname",
		"Show the name of the current buffer.",
		"",
		"",
		"",
		"bufname", "")

	weechat.hook_command("decide",
		"Get Python's random module to make a decision.",
		"question || op1 or op2 or op3 ... || op1 | op2 | op3 | ...",
		"",
		"",
		"decide", "")
