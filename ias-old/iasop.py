import sys

opcodes = {
	"NOP":     "00",

	"LOAD":    "01", #      M(X) => AC
	"LOADN":   "02", # -1 * M(X) => AC
	"LOADA":   "03", # abs(M(X)) => AC
	"LOADMQ":  "0A", #      [MQ] => AC
	"LOADMQM": "09", #      M(X) => MQ
	"STOR":    "21", #      [AC] => M(X)

	"JUMPL":   "0D", # JUMP  M(X, 0:19)
	"JUMPR":   "0E", # JUMP  M(X,20:39)
	"JUMP+L":  "0F", # JUMP+ M(X, 0:19)
	"JUMP+R":  "10", # JUMP+ M(X,20:39)

	"ADD":     "05", #      [AC] + M(X) => AC
	"ADDA":    "07", # [AC] + abs(M(X)) => AC
	"SUB":     "06", #      [AC] - M(X) => AC
	"SUBA":    "08", # [AC] - abs(M(X)) => AC
	"MUL":     "0B", #      [MQ] * M(X) => AC:MQ
	"DIV":     "0C", #      [MQ] / M(X) => MQ; [MQ] % M(X) => AC

	"LSH":     "14", # [AC] << 1 => AC
	"RSH":     "15", # [AC] >> 1 => AC

	"STORL":   "12", # [AC, 8:19] => M(X, 8:19)
	"STORR":   "13"  # [AC, 8:19] => M(X,20:39)
}

labels = {}

def label(label, addr, right):

	if label in labels:
		print("A label {} já foi usada.".format(label), file=sys.stderr)
		raise SystemExit

	labels[label] = (addr, right)

def oper(op, operand):

	if op not in opcodes:
		print("Instrução desconhecida: {}.".format(op), file=sys.stderr)
		raise SystemExit

	return "{} {}".format(opcodes[op], operand)

def load(oper):

	opers = list(map(str.strip, oper.split(",")))

	if len(opers) > 1 and opers[0] == "MQ":
		return "{} {}".format(opcodes["LOADMQM"], opers[1])
	elif len(opers) > 1:
		print("Instrução não reconhecida: LOAD {}.".format(oper),
				file=sys.stderr)
		raise SystemExit
	elif oper == "MQ":
		return opcodes["LOADMQ"] + " 000"
	elif oper.startswith("-"):
		return "{} {}".format(opcodes["LOADN"], oper[1:])
	elif oper.startswith("|"):
		return "{} {}".format(opcodes["LOADA"], oper.strip("|"))

	return "{} {}".format(opcodes["LOAD"], oper)

def jump(op, label):

	if label not in labels:
		print("A label {} não existe.".format(label), file=sys.stderr)
		raise SystemExit

	addr, right = labels[label]

	op += "R" if right else "L"

	return "{} {:03x}".format(opcodes[op], addr).upper()

def parselabels(asm):

	_addr = 0x000
	raddr = False
	rms   = []

	for i in asm:
		l = i.split()[0]

		if l.endswith(":"):
			label(l.rstrip(":"), _addr, raddr)
			rms.append(i)
			continue

		if raddr:
			_addr += 1

		raddr = not raddr

	return rms
