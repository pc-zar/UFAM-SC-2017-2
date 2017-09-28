#include <stdio.h>
#include <stdlib.h>
#include "file.h"


struct noProcesso {
	int pid;
	int tempoIngresso;
	int duracao;
	int prioridade;
	int tipo;
	struct noProcesso* prox;
};

int main(void) {
	struct noProcesso *plist, *ptmp;
    	plist       = init(1, 4, 2, 0, 0);
        plist->prox = init(2, 1, 1, 0, 0); ptmp = plist->prox;
	ptmp->prox  = init(3, 4, 2, 0, 0); ptmp = ptmp->prox;
	ptmp->prox  = init(4, 0, 3, 0, 0); ptmp = ptmp->prox;
	ptmp->prox  = init(5, 2, 2, 0, 0);
	
	//tt = 4
	//tw = 2

	printf("PROCESSOS ANTES DO ESCALONAMENTO:\n");	
	printListaProcessos(plist);

	return 0;
};

struct noProcesso *init(int pid, int tempoIngresso, int duracao, int prioridade, int tipo){
	struct noProcesso *proc;
 	proc = (struct noProcesso*)malloc(sizeof(struct noProcesso)); 
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

void printListaProcessos(struct noProcesso *proc){
	while(proc != NULL){
		printf("PID: %d | tempo: %d | dur: %d | prio: %d | tipo: %d \n", 
				proc->pid, proc->tempoIngresso, proc->duracao, proc->prioridade, proc->tipo);
		proc = proc->prox;
	};
	printf("\n");
};


void fcfs(struct noProcesso *proc){
	int aux = 0;
	








};
