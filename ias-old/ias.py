#!/bin/env python3

import sys
import re

import iasop

curraddr  = 0x000
rightaddr = False

jumpops = ["JUMP", "JUMP+"]
loadops = ["LOAD"]

# abre o arquivo e filtra linhas vazias e de comentário
with open(sys.argv[1], "r") as f:
	asm = f.readlines()

for i,l in enumerate(asm):
	if "#" in l:
		asm[i] = l[:l.find("#")]

asm = [ l.strip() for l in asm if l.strip() ]

# processa labels, removendo as linhas dedicadas a elas
for line in iasop.parselabels(asm):
	asm.remove(line)

# converte instrução por instrução para hexadecimal
for inst in asm:

	_split = inst.split(None, 1)

	opc = _split[0].upper()
	opa = _split[1] if len(_split) > 1 else "000"
	opa = re.sub("M\(([0-9a-fA-F]+)\)", "\\1", opa)

	if not rightaddr:
		print("{:03x}".format(curraddr).upper(), end=" ")

	if opc in jumpops:
		hexstr = iasop.jump(opc, opa)
	elif opc in loadops:
		hexstr = iasop.load(opa)
	else:
		hexstr = iasop.oper(opc, opa)

	print(hexstr, end = "\n" if rightaddr else " ")

	if rightaddr:
		curraddr += 1

	rightaddr = not rightaddr

# caso faltem os 20 bits da última célula
if rightaddr:
	print("00 000")
