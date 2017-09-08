	LOAD   MQ, M(100) #      [0x100] => MQ
	MUL        M(101) # [MQ]*[0x101] => MQ
	LOAD           MQ #         [MQ] => AC
	STOR       M(102) #         [AC] => 0x102

# imagine que uma variável _v está no endereço 0x111 e que o valor `-1` está no
# endereço 0x112...

dowhile:
	LOAD       M(111) # do {
	ADD        M(112) #   --_v;
	STOR       M(111) # }

	LOAD   MQ, M(111) # while (_v > 0);
	ADD        M(112) # <- feito multiplicando por -1 (0x112)
	JUMP+     dowhile #

# dada uma variável _v em 0x111, e uma variável _l em 0x112, além do valor `1`
# no endereço 0x121, podemos realizer o seguinte loop while:

while_s:
	LOAD      M(111) #
	SUB       M(121) # while (_v > 0) {
	JUMP+    while_e #

	LOAD      M(111) #
	RSH              # _v >>= 1;
	STOR      M(111) #

	LOAD      M(112) #
	ADD       M(121) # ++_l;
	STOR      M(112) #

	JUMP     while_s # }

# resto do código
while_e:
	JUMP for_loop # <- similar a um `goto forloop;`
	LOAD      M(000) #
	RSH              # inalcançável
	STOR      M(000) #

for_loop:

# com o valor `3` no endereço 0x131, e o valor `6` no endereço 0x132, além das
# variáveis _a e _b nos endereços 0x141 e 0x142, respectivamentes, podemos
# realizar o seguinte loop for:
#
# 	for (_a += 6; _a >= 3; _a -=3)
# 		_b *= 3;

	LOAD       M(141) #
	ADD        M(132) # for (_a += 6; ...)
	STOR       M(141) #
for_s:
	LOAD       M(141) #
	SUB        M(131) # for (...; _a >= 3; ...)
	JUMP+       for_e #

	LOAD   MQ, M(142) #
	MUL        M(131) # _b *= 3;
	LOAD           MQ #
	STOR       M(142) #

	LOAD       M(141) #
	SUB        M(131) # for (...; _a -=3)
	STOR       M(141) #

	JUMP        for_s # }

# resto do código
for_e:
	# ...
