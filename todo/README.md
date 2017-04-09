# todo

A simple program to manage a todo list, separated by lines, like this:

	do thing X
	do thing Y

There are some things to take into consideration:

- I'm using 512 bytes long buffers for each line, meaning the program function
  properly for lines up to 510 characters (`'\n'` and `'\0'` come at the end).
- Unlike the script I wrote in Python(not in this repo, too ugly), it doesn't
  support long options like `--add`, `--delete`, etc. I opted not to use
  `getopt_long()` for brevity. It also doesn't support `-h` or `--help`.
- There's no reading environment variables, as would be necessary for XDG
  compliance. This isn't a script I made thinking of other people using it. It's
  just something I'm putting here for future reference or in case anyone feels
  interested in what I've worked on. File paths are hardcoded.
- I'm using a copy file to delete entries. That works for small files, and I
  don't plan on having too many things to do. Still, have that in mind.
- I'm ignoring additional options by not having `getopt()` handled in a loop.
  What that means is the program WILL ignore other options if ran like this:
  `programname -a "option here" -l`.
- `todo.sh` is invoked in a `system()` call. That's just a script that runs
  `dunstify` to send me a notification. Could I use libnotify manually?
  Possibly. Do I want to? Nah, I already wrote `todo.sh`, which is in `$PATH`,
  why bother?
