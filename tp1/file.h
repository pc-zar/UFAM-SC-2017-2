#ifndef FILE_H_   
#define FILE_H_

struct noProcesso *init(int pid, int tempoIngresso, int duracao, int prioridade, int tipo);
void printListaProcessos(struct noProcesso *proc);
void fcfs(struct noProcesso *proc);
#endif
