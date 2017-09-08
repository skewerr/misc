# Em C:
#
# 	int
# 	sp(const int *v1, const int *v2, const int L)
# 	{
# 		int s = 0;
# 		int i;
#
# 		for (i = 0; i < L; ++i)
# 			s += v1[i] * v2[i];
#
# 		return s;
# 	}

	LOAD     M(3FD)
	NOP             # carrega o endereço na instrução de LOAD
	LOAD     M(3FE)
	NOP             # carrega o endereço na instrução de MUL

loop:
	LOAD    -M(3FF) # carrega o tamanho do vetor * -1
	ADD      M(0FF) # adiciona o iterador(i)
	JUMP+    loop_e # sai do loop se o valor for não-negativo (i >= L)

	LOAD MQ, M(000) # carrega do vetor 1
	MUL      M(000) # multiplica pela posição no vetor 2
	LOAD MQ         # [MQ] => AC
	ADD      M(0FD) # + s
	STOR     M(0FD) # [AC] => s

	LOAD     M(0FF) #
	ADD      M(0FE) # ++i;
	STOR     M(0FF) #

	LOAD     M(3FD) # carrega o endereço do primeiro vetor
	ADD      M(0FF) # adiciona o iterador(i)
	NOP             # substitui o endereço na instrução de LOAD
	LOAD     M(3FE) # carrega o endereço do segundo vetor
	ADD      M(0FF) # adiciona o iterador(i)
	NOP             # substitui o endereço na instrução de MUL

	JUMP       loop # de volta ao começo do loop
loop_e:
	LOAD     M(0FD) # carrega s em AC
