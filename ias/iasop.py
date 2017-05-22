import sys
import re

hexcodes = { "NOP":     "00"   # no-op
           , "LOADMEM": "01"   # load from memory
           , "LOADNEG": "02"   # load from memory times -1
           , "LOADABS": "03"   # load from memory, absolute val
           , "ADD":     "05"   # add value from memory
           , "SUB":     "06"   # subtract value from memory
           , "ADDABS":  "07"   # add absolute value from memory
           , "SUBABS":  "08"   # subtract absolute value from memory
           , "LOADMQM": "09"   # load value from memory into MQ
           , "LOADMQ":  "0A"   # load value from MQ
           , "MUL":     "0B"   # multiply value from memory
           , "DIV":     "0C"   # divide by value from memory
           , "JUMPL":   "0D"   # jump to the instruction on the left
           , "JUMPR":   "0E"   # jump to the instruction on the right
           , "JUMPL+":  "0F"   # conditional jump to instruction on the left
           , "JUMPR+":  "10"   # conditional jump to instruction on the right
           , "STORAL":  "12"   # update address field of a left instruction
           , "STORAR":  "13"   # update address field of a right instruction
           , "LSH":     "14"   # shift bits to the left
           , "RSH":     "15"   # shift bits to the right
           , "STORMEM": "21" } # store value in memory

labels = {}

loadops = ["LOAD"]

# regex patterns

negpattern  = re.compile("^\-M\(([0-9a-fA-F]+)\)$")
abspattern  = re.compile("^\|M\(([0-9a-fA-F]+)\)\|$")
mempattern  = re.compile("^M\(([0-9a-fA-F]+)\)$")
negpatternl = re.compile("^\-(.+)$")
abspatternl = re.compile("^\|(.+)\|$")

# translation

def translate(operation, operand):

    if operation in loadops:
        return loadtranslate(operand)

    return directtranslate(operation, operand)

def loadtranslate(operand):

    if operand.startswith("MQ"):
        return loadmqtranslate(operand)

    absmatch = abspattern.match(operand)
    negmatch = negpattern.match(operand)
    memmatch = mempattern.match(operand)

    if absmatch: return hexcodes["LOADABS"] + " " + absmatch.group(1)
    if negmatch: return hexcodes["LOADNEG"] + " " + negmatch.group(1)
    if memmatch: return hexcodes["LOADMEM"] + " " + memmatch.group(1)

    absmatch = abspatternl.match(operand)
    negmatch = negpatternl.match(operand)

    operand = absmatch.group(1) if absmatch else \
              negmatch.group(1) if negmatch else \
              operand

    operation = "LOADABS" if absmatch else \
                "LOADNEG" if negmatch else \
                "LOADMEM"

    return "{} {:03X}".format(hexcodes[operation], getlabel(operand)[0])

def loadmqtranslate(operand):

    if operand == "MQ":
        return hexcodes["LOADMQ"] + " 000"

    operand = operand[operand.find(",")+1:].strip()
    match   = mempattern.match(operand)

    if match:
        return hexcodes["LOADMQM"] + " " + match.group(1)

    return "{} {:03X}".format(hexcodes["LOADMQM"], getlabel(operand)[0])

def directtranslate(operation, operand):

    try:
        return "{} {}".format(hexcodes[operation], operand)
    except KeyError:
        print("Instruction not recognized:", operation, file=sys.stderr)
        raise SystemExit

# labels

def collectlabels(lines):

    address = 0x000

    for i, line in enumerate(lines):
        label = line.split()[0]

        if label.endswith(":"):
            labels[label[:-1]] = (int(address), bool(address % 1))
            lines[i] = (line.split(maxsplit=1) + [""])[1]

            if lines[i] == "":
                continue

        address += 0.5

    return noemptylines(lines)

def getlabel(label):

    if label not in labels:
        print("Unknown label:", label, file=sys.stderr)
        raise SystemExit

    return labels[label]

# lines manipulation

def filtercomments(lines):

    for i,l in enumerate(lines):
        if "#" in l:
            lines[i] = l[:l.find("#")]

    return noemptylines(lines)

def padinstructions(lines):

    for i, l in enumerate(lines):
        if len(l.split(maxsplit=1)) < 2:
            lines[i] += " 000"

    return lines

def noemptylines(lines):

    return list(filter(bool, map(str.strip, lines)))

# misc functions

def pairs(iterable):

    it = iter(iterable)
    return zip(it, it)
