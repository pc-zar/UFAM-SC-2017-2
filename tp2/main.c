#include <stdio.h>
#include <time.h>

typedef struct NodeCliente{
	int categoria;
	int tempo;
	struct NodeCliente *prox;
} nodeCliente_t ;

int main(){
	srand(time(NULL));
	nodeCliente_t *oficialHead, *sgtHead, *caboHead = NULL;
	int catTemp = 0;
	int tempoTemp = 0;

	for(int i = 0; i < 1000; i++){
		catTemp = rand_range(0, 3);
		switch(catTemp){
			case 1:
				tempoTemp = rand_range(4, 6);				
				//caso seja a primeira vez q a lista esteja sendo preenchida
				if(oficialHead == NULL){
					oficialHead = malloc(sizeof(nodeCliente_t));
					oficialHead->categoria = 1;
					oficialHead->tempo = tempoTemp;
					oficialHead->prox = NULL;
				//caso a lista já possua uma head, adicionar um item a lista
				} else {
					nodeCliente_t *atual = oficialHead;

					while(atual->prox != NULL){
						atual = atual->prox;
					}

					atual->prox = malloc(sizeof(nodeCliente_t));
					atual->prox->categoria = 1;
					atual->prox->tempo = tempoTemp;
					atual->prox->prox = NULL;
				}
				break;
			case 2:
				tempoTemp = rand_range(2, 4);				
				//caso seja a primeira vez q a lista esteja sendo preenchida
				if(sgtHead == NULL){
					sgtHead = malloc(sizeof(nodeCliente_t));
					sgtHead->categoria = 2;
					sgtHead->tempo = tempoTemp;
					sgtHead->prox = NULL;
				//caso a lista já possua uma head, adicionar um item a lista
				} else {
					nodeCliente_t *atual = sgtHead;

					while(atual->prox != NULL){
						atual = atual->prox;
					}

					atual->prox = malloc(sizeof(nodeCliente_t));
					atual->prox->categoria = 2;
					atual->prox->tempo = tempoTemp;
					atual->prox->prox = NULL;
				}
				break;
			case 3:
				tempoTemp = rand_range(1, 3);				
				//caso seja a primeira vez q a lista esteja sendo preenchida
				if(caboHead == NULL){
					caboHead = malloc(sizeof(nodeCliente_t));
					caboHead->categoria = 3;
					caboHead->tempo = tempoTemp;
					caboHead->prox = NULL;
				//caso a lista já possua uma head, adicionar um item a lista
				} else {
					nodeCliente_t *atual = caboHead;

					while(atual->prox != NULL){
						atual = atual->prox;
					}

					atual->prox = malloc(sizeof(nodeCliente_t));
					atual->prox->categoria = 3;
					atual->prox->tempo = tempoTemp;
					atual->prox->prox = NULL;
				}
				break;
			case 0:
				printf("PAUSA!\n");	
				break;
		}
	}
	printLista(oficialHead);
	printLista(sgtHead);
	printLista(caboHead);
	return 0;
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





