#include <stdio.h>
#include <stdlib.h>
#include "file.h"


struct Processo {
	int pid;
	int tempoIngresso;
	int duracao;
	int prioridade;
	int tipo;
	struct Processo* prox;
};

int main(void) {
	//FILE* f;
	//f = fopen("processos.txt", "r");
	
	struct Processo *plist, *ptmp;
    	plist       = init(1, 0, 1, 0, 0);
        plist->prox = init(2, 0, 1, 0, 0); ptmp = plist->prox;
	ptmp->prox  = init(3, 0, 1, 0, 0); ptmp = ptmp->prox;
	ptmp->prox  = init(4, 0, 1, 0, 0); ptmp = ptmp->prox;
	ptmp->prox  = init(5, 0, 1, 0, 0);
	
	listaProcessos(plist);

	//printf("Hello World");
	return 0;
};

struct Processo *init(int pid, int tempoIngresso, int duracao, int prioridade, int tipo){
	struct Processo *proc;
 	proc = (struct Processo*)malloc(sizeof(struct Processo)); 
  	if (proc == NULL) {
		printf("Erro!");
		exit(1);
	};
    	
	proc->pid = pid;
	proc->tempoIngresso = tempoIngresso;
	proc->duracao = duracao;
	proc->prioridade = prioridade;
	proc->tipo = tipo;
	proc->prox = NULL;
	return(proc);
};

void listaProcessos(struct Processo *proc){
	struct Processo *t = proc;
	while(t != NULL){
		printf("%d\n", t->pid);
		t = t->prox;
	};
	printf("\n");
};
