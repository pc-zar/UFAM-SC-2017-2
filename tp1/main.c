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
	
	

	printf("Hello World");
	return 0;
}

struct Processo* init(int pid, int tempoIngresso, int duracao, int prioridade, int tipo){
	struct Processo* proc;
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
}

void listaProcessos(struct Processo* proc){
	struct Processo* t = proc;
	while(t != NULL){
		printf(t->pid, t->tempoIngresso, t->duracao, t->prioridade, t->tipo);
	}	
}
