#include <stdio.h>

struct Processo {
	int pid;
	int tempoIngresso;
	int duracao;
	int prioridade;
	int tipo;
	struct Processo* prox;
};

int main(){

	printf("Hello World");
	return 0;

}
