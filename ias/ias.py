#!/bin/env python3

import sys
import iasop

with open(sys.argv[1], "r") as asmfile:
    asmlines = iasop.filtercomments(asmfile.readlines())

asmlines = iasop.collectlabels(asmlines)

if len(asmlines) % 2:
    asmlines.append("NOP")

asmlines = iasop.padinstructions(asmlines)

address = 0x000

for linst, rinst in iasop.pairs(asmlines):

    loperation, loperand = linst.split(maxsplit=1)
    roperation, roperand = rinst.split(maxsplit=1)

    print("{:03X} {} {}".format(address, iasop.translate(loperation, loperand),
                                iasop.translate(roperation, roperand)))

    address += 1
