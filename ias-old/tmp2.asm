	LOAD MQ, M(105) # [0x105] => MQ  (x = 3500m)
	MUL      M(106) # multiplica por [0x106](g = 10m/s²)
	LOAD MQ         # de MQ para o AC
	STOR     M(112) # armazena g * x em 0x112 (vo)
	RSH             # divide por 2
	STOR     M(111) # guarda em 0x111 (v)

	LOAD     M(106) # carrega g, que será usado como iterador do loop
	SUB      M(107) # subtrai de 1, em 0x107
	STOR     M(106) # guarda de volta em g

loop:
	LOAD     M(112) # carrega v0 para AC
	DIV      M(111) # divide por v
	LOAD MQ         # carrega o quociente em AC
	ADD      M(111) # adiciona v (AC = v + vo/v)
	RSH             # divide por 2 (AC = (v + vo/v)/2)
	STOR     M(111) # guarda em v (v = (v + vo/v)/2)

	LOAD     M(106) # carrega g
	SUB      M(107) # subtrai 1
	STOR     M(106) # guarda em g

	JUMP+      loop # jump para loop se g < 0
