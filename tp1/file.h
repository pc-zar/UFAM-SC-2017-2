#ifndef FILE_H_   
#define FILE_H_

struct Processo* init(int pid, int tempoIngresso, int duracao, int prioridade, int tipo);
void listaProcessos(struct Processo* proc)
void fcfs(struct Processo* proc);
#endif
