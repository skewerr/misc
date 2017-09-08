# ias-old

Assembler velho para o simulador de IAS que eu fiz às pressas no primeiro
semestre de 2017.

Observações:

- Tem suporte a labels;
- Tem suporte a posições explícitas de memória (`LOAD M(100)` vs. `LOAD UM`);
- Não entende anotações como `.org` ou `.word` \*

\* É possível utilizar endereços explícitos para variáveis ou até mesmo usar
labels, mas algo como `X: 00 00 00 00 00` causa erro, então sugiro que coloque
os valores no código final da seguinte forma:

```
LOAD M(100)
...
```

Após rodar `ias.py arquivo.asm`...

```
000 01 100 ...
```

... colocar os valores manualmente:

```
000 01 100 ...
...
100 00 00 00 0A BC
```

## Exemplos

Há alguns arquivos `.asm` no repositório que exemplificam o uso do programa.
