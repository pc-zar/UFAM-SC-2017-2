#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_CLIENTES 1000
#define MAX_BARBEARIA 20
#define MAX_BARBEIROS 1

sem_t oficial, sgt, cabo;

typedef struct NodeCliente{
	int categoria;
	int tempo;
	struct NodeCliente *prox;
} nodeCliente_t ;

//prototypes
nodeCliente_t *initFilaEspera();
void printLista(nodeCliente_t *head);
nodeCliente_t *appendNodeCliente(nodeCliente_t *head, int catTemp, int tempoTemp);
nodeCliente_t *criaNode();
int qtdAtualBarbearia(nodeCliente_t *oficial, nodeCliente_t *sgt, nodeCliente_t *cabo);
int rand_range(int min_n, int max_n);


int main(void){
	srand(time(NULL));
	nodeCliente_t *filaEspera, *oficial, *sgt, *cabo, *cursor;
	
	filaEspera = initFilaEspera();
	oficial = NULL;
	sgt = NULL;
	cabo = NULL;

	cursor = filaEspera;
	while(cursor != NULL){
		if(qtdAtualBarbearia(oficial, sgt, cabo) < MAX_BARBEARIA){
			switch(cursor->categoria){
				case 1:
					oficial = appendeNodeCliente(oficial, 1, cursor->tempo);
					break;
				case 2:
					sgt = appendeNodeCliente(sgt, 2, cursor->tempo);
					break;
				case 3:
					cabo = appendeNodeCliente(cabo, 3, cursor->tempo);
					break;
				default:
					printf("PASUDASDHJAKDHJKDHADSJDA");
					break;
			
			}
		} else {
			printf("BARBEARIA CHEIA!!!!");
		}
		cursor = cursor->prox;
	}	

	return 0;
}

int qtdAtualBarbearia(nodeCliente_t *oficial, nodeCliente_t *sgt, nodeCliente_t *cabo){
	int qtd = 0;
	nodeCliente_t *cursor = oficial;

	while(cursor != NULL){
		qtd++;
		cursor = cursor->prox;
	}

	cursor = sgt;

	while(cursor != NULL){
		qtd++;
		cursor = cursor->prox;
	}
	
	cursor = cabo;

	while(cursor != NULL){
		qtd++;
		cursor = cursor->prox;
	}

	return qtd;
}

nodeCliente_t *initFilaEspera(){
	nodeCliente_t *entrada = NULL;
	int catTemp = 0;
	int tempoTemp = 0;
	for(int i = 0; i < MAX_CLIENTES; i++){
		catTemp = rand_range(0, 3);
		switch(catTemp){
			case 1: //oficial
				tempoTemp = rand_range(4, 6);
				break;
			case 2: //sgt
				tempoTemp = rand_range(2, 4);
				break;
			case 3: //cabo
				tempoTemp = rand_range(1, 3);					
				break;
			default: //pausa
				tempoTemp = 0;
				break;
		}
		entrada = appendNodeCliente(entrada, catTemp, tempoTemp);
	}
	return(entrada);
}

void printLista(nodeCliente_t *head){
	nodeCliente_t *cursor = head;

	while(cursor != NULL){
		printf("CAT: %d | TEMPO: %d\n", cursor->categoria, cursor->tempo);
		cursor = cursor->prox;
	}
}

nodeCliente_t *criaNode(int catTemp, int tempoTemp){
	nodeCliente_t *node;

	node = malloc(sizeof(nodeCliente_t));
	node->categoria = catTemp;
	node->tempo = tempoTemp;
	node->prox = NULL;

	return node; 
}

nodeCliente_t *appendNodeCliente(nodeCliente_t *head, int catTemp, int tempoTemp){
	if(head == NULL){
		head = (nodeCliente_t*)malloc(sizeof(nodeCliente_t));
		head->categoria = catTemp;
		head->tempo = tempoTemp;
		head->prox = NULL;
	} else {
		nodeCliente_t *cursor = head;
		//caso entre aqui, criar novo node
		while(cursor->prox != NULL){
			cursor = cursor->prox;
		}
		
		//tail of current list, previously null, now receives the new node
		nodeCliente_t *newNode = NULL;
		
		newNode = criaNode(catTemp, tempoTemp);
		cursor->prox = newNode;
	}

	return head;	
}

int rand_range(int min_n, int max_n){
	return rand() % (max_n - min_n + 1) + min_n;
}
