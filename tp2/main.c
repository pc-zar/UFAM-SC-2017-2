#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct NodeCliente{
	int categoria;
	int tempo;
	struct NodeCliente *prox;
} nodeCliente_t ;

//prototypes
nodeCliente_t *initFila();
void printLista(nodeCliente_t *head);
int rand_range(int min_n, int max_n);

int main(void){
	srand(time(NULL));
	printLista(initFila());


	return 0;
}

nodeCliente_t *initFila(){
	nodeCliente_t *entrada = NULL;
	int catTemp = 0;
	int tempoTemp = 0;
	for(int i = 0; i < 1000; i++){
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

		if(entrada == NULL){
			entrada = malloc(sizeof(nodeCliente_t));
			entrada->categoria = catTemp;
			entrada->tempo = tempoTemp;
			entrada->prox = NULL;
		} else {
			nodeCliente_t *temp = entrada;

			while(temp->prox != NULL){
				temp = temp->prox;
			}

			temp->prox = malloc(sizeof(nodeCliente_t));
			temp->prox->categoria = catTemp;
			temp->prox->tempo = tempoTemp;
			temp->prox->prox = NULL;
		}
	}
	return(entrada);
}


void printLista(nodeCliente_t *head){
	nodeCliente_t *atual = head;

	while(atual != NULL){
		printf("CAT: %d | TEMPO: %d\n", atual->categoria, atual->tempo);
		atual = atual->prox;
	}
}

int rand_range(int min_n, int max_n){
	return rand() % (max_n - min_n + 1) + min_n;
}





