#!/usr/bin/env python3

import sys
import time

ins_tape = ""            	# instructions tape
lop_tape = []            	# loop indexes tape
dat_tape = bytearray([0])	# data tape
dat_indx = 0             	# data index (will be used as pointer)
ins_indx = 0             	# instruction index

out_str = ""  	# output string
p_sleep = 0.03	# loop sleep

# increment/decrement current cell value
def inc_cell(_):

	try:
		dat_tape[dat_indx] += 1
	except ValueError:
		dat_tape[dat_indx] = 0

	return _ + 1

def dec_cell(_):

	try:
		dat_tape[dat_indx] -= 1
	except ValueError:
		dat_tape[dat_indx] = 255

	return _ + 1

# increment/decrement cell pointer
def inc_pntr(_):

	global dat_indx

	dat_indx += 1

	while len(dat_tape) <= dat_indx:
		dat_tape.append(0)

	return _ + 1

def dec_pntr(_):

	global dat_indx

	if dat_indx != 0:
		dat_indx -= 1
	else:
		dat_tape.insert(0, 0)

	return _ + 1

# start/end loop
def start_loop(indx):

	lop_tape.append(indx + 1)

	return indx + 1

def end_loop(indx):

	try:
		if dat_tape[dat_indx] != 0:
			return lop_tape[-1]
		else:
			lop_tape.remove(lop_tape[-1])

			return indx + 1
	except IndexError:
		return indx + 1 # ignore unmatched closing loop

# character io
def read_char(_):

	dat_tape[dat_indx] = ord(sys.stdin.read(1)[0])

	return _ + 1

def print_char(_):

	global out_str

	out_str += chr(dat_tape[dat_indx])
#	print(chr(dat_tape[dat_indx]), end='')

	return _ + 1

# function dictionary with all of brainfuck's symbols
fun_dict = {
	'+': inc_cell,
	'-': dec_cell,
	'>': inc_pntr,
	'<': dec_pntr,
	'[': start_loop,
	']': end_loop,
	',': read_char,
	'.': print_char
}

# read the first argument, try to open it as a file
with open(sys.argv[1], "r") as inf:
	ins_tape = ''.join([c for c in inf.read() if c in fun_dict.keys()])

# getting characters from a string
def ins_prep(indx, offset):

	prep_str = ins_tape[indx - offset:indx]
	ch_offset = offset

	while not prep_str:
		ch_offset -= 1
		prep_str = ins_tape[indx - ch_offset:indx]
	
	while len(prep_str) != offset:
		prep_str = " " + prep_str
	
	return prep_str

# let's go through the instructions, now
while ins_indx < len(ins_tape):

	op_c = ins_tape[ins_indx]
	old_indx = ins_indx

	# using our function dict
	ins_indx = fun_dict[op_c](ins_indx)

	print("\033[1;1H", end="")
	print("  Output:", out_str.replace('\n', "\\n"))
	print("   Cells:", '\t'.join(["{:03d}".format(_) for _ in dat_tape]))
	print(" Pointer:", "   \t" * dat_indx, " ^", " " * 20)
	print("Operator:", op_c)

	# rewind the tape if we're caught by the loop
	# `and ins_indx != old_indx` takes care of infinite loops
	if ins_indx < old_indx + 1 and ins_indx != old_indx:
		while old_indx != ins_indx:
			old_indx -= 1
			print("\033[5;1H", end="")
			print("    Next:", ins_prep(old_indx, 35), "\033[34m" +
				ins_tape[old_indx] + "\033[0m", ins_tape[old_indx+1:old_indx+36],
				" " * 20)

			time.sleep(p_sleep)
	else:
		print("    Next:", ins_prep(ins_indx, 35), "\033[31m" +
			(ins_tape[ins_indx] if ins_indx < len(ins_tape) else "HALT") + "\033[0m",
			ins_tape[ins_indx+1:ins_indx+36], " " * 20)

		time.sleep(p_sleep)
