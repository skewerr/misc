# ias

This is an "assembler" for the [IAS machine](https://en.wikipedia.org/wiki/IAS_machine).

More specifically, it is a memory map generator for [a certain IAS machine
simulator](http://www.ic.unicamp.br/~edson/disciplinas/mc404/2016-2s/abef/IAS-sim/).

It was started as an attempt to minimize my work in a Computer Architecture
class, when the teacher assigned us to write programs for the aforementioned IAS
machine simulator. I also thought it would be good practice for any future
assignments in the Computer Science course that involved string manipulation or
anything related to assembler code.

Alas, I will attempt to complete this with width annotations and whatnot. Expect
a link to an online version of this assembler in the future as I plan to email
the teacher suggesting he let his future students use it.

For the time being only direct translation of the operations, as stipulated by
the `hexcodes` dictionary in `iasop.py`, is supported. If it is still the case
in a day or two, bother me to get off my chair and at least add labels.

## Passes

This is a rewrite of the (messy) script I used for the assignment, so it is very
incomplete. Here are the planned passes for assembly, however:

1. Filter comments.
2. Parse annotations. (`.org`, `.word`, `.align`)
3. Collect labels.
4. Translate operations and labels.

These steps may change depending on how poor my grasp and shallow my knowledge
of Python are, so please bear with me if you're judging this part of perhaps one
of the worst repositories on GitHub.
