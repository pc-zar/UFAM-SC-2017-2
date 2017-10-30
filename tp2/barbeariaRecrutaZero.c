#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_CLIENTES 50
#define MAX_BARBEARIA 25
#define MAX_BARBEIROS 1

typedef struct NodeCliente{
	int categoria;
	int tempo;
	struct NodeCliente *prox;
} nodeCliente_t ;

typedef struct ClienteParams {
	int categoria;
	int tempo;
} clienteParams_t;

sem_t semOficial, semSgt, semCabo;
int qtdSleepTainha;
int qtdPausas;

//BARBEARIA
nodeCliente_t *filaEspera, *oficial, *sgt, *cabo;

//prototypes
nodeCliente_t *initFilaEspera();
void printLista(nodeCliente_t *head);
nodeCliente_t *appendNodeCliente(nodeCliente_t *head, int catTemp, int tempoTemp);
nodeCliente_t *criaNode();
int qtdAtualBarbearia();
void printBarbearia();
int rand_range(int min_n, int max_n);
void *sgtTainha();
void *recrutaZero();
nodeCliente_t *shiftHead(nodeCliente_t *head);

int main(void){
	srand(time(NULL));
	filaEspera = initFilaEspera();
	int inputQtdSleepTainha = 0;
	int qtdSleepTainhaLock = 1;
	pthread_t tSgtTainha, tRecrutaZero;
	oficial = NULL;
	sgt = NULL;
	cabo = NULL;

	while(qtdSleepTainhaLock == 1){	
		printf("Por quanto tempo (em segundos) Sgt. Tainha deve dormir? (escolha de 1 ate 5):");
		scanf("%d", &inputQtdSleepTainha);

		if((inputQtdSleepTainha >= 1) && (inputQtdSleepTainha <= 5)){
			qtdSleepTainha = inputQtdSleepTainha;
			qtdSleepTainhaLock = 0;
		} else {
			printf("ESCOLHA DE 1 ATE 5!\n\n");
		}
	}
	
	sem_init(&semOficial, 0, 1);
	sem_init(&semSgt, 0, 1);
	sem_init(&semCabo, 0, 1);

	pthread_create(&tSgtTainha, NULL, sgtTainha, NULL);	
	pthread_create(&tRecrutaZero, NULL, recrutaZero, NULL);	

	pthread_join(tSgtTainha, NULL);
	pthread_join(tRecrutaZero, NULL);
	
	sem_destroy(&semOficial);
	sem_destroy(&semSgt);
	sem_destroy(&semCabo);

	printBarbearia();

	//printf("\nBARBEARIA ANTIGA ACIMA\n");

	//recrutaZero();

	//printf("\n\nNOVA BARBEARIA DELETADA!!!!!\n");
	//printBarbearia();
	return 0;
}

void *recrutaZero(){
	while(qtdAtualBarbearia() != 0){
		nodeCliente_t *cursor = oficial;
		//primeiro remocao de oficiais
		while(cursor != NULL){
			int tempo = cursor->tempo;
			sem_wait(&semOficial);
			sleep(tempo);
			printf("REMOCAO EM 1\n");
			oficial = shiftHead(oficial);
			sem_post(&semOficial);
			cursor = oficial;
		}

		
		cursor = sgt;
	
		//remocao de sargentos
		while(cursor != NULL){
			int tempo = cursor->tempo;
			sem_wait(&semSgt);
			sleep(tempo);
			printf("REMOCAO EM 2\n");
			sgt = shiftHead(sgt);
			sem_post(&semSgt);
			cursor = sgt;
		}
		
		cursor = cabo;
		//remocao de cabos
		while(cursor != NULL){
			int tempo = cursor->tempo;
			sem_wait(&semCabo);
			sleep(tempo);
			printf("REMOCAO EM 3\n");
			cabo = shiftHead(cabo);
			sem_post(&semCabo);
			cursor = cabo;
		}
	}
	
		pthread_exit(NULL);	
		return NULL;	
}

void *sgtTainha(){
	qtdPausas = 0;
	nodeCliente_t *cursor;
	cursor = filaEspera;
	
	while((cursor != NULL) && (qtdPausas != 3)){
		if(cursor->categoria != 0){
			if(qtdAtualBarbearia() < MAX_BARBEARIA){
				switch(cursor->categoria){
					case 1:
						sem_wait(&semOficial);
						printf("INSERCAO EM 1!!!!\n");
						oficial = appendNodeCliente(oficial, 1, cursor->tempo);	
						sem_post(&semOficial);
						break;
					case 2:
						//printf("INSERIU EM SGT\n");
						sem_wait(&semSgt);
						printf("INSERCAO EM 2!!!\n");
						sgt = appendNodeCliente(sgt, 2, cursor->tempo);	
						sem_post(&semSgt);
						break;
					case 3:
						//printf("INSERIU EM CABO!\n");
						sem_wait(&semCabo);
						printf("INSERCAO EM 3!!!\n");
						cabo = appendNodeCliente(cabo, 3, cursor->tempo);	
						sem_post(&semCabo);
						break;
				}
			} else {
				//printf("EXPULSO!!!\n");
			}
		} else {
			//printf("PAUSA!\n");
			qtdPausas++;
		}
		//printBarbearia();
		cursor = cursor->prox;
		sleep(qtdSleepTainha);
	}
	//printf("\nSAIU DA FILA DE ESPERA");
	//FIM DA FILA OU 3 PAUSAS!!!!!
	//pthread_mutex_destroy(&lock);
	pthread_exit(NULL);
	return NULL;
}

void printBarbearia(){
	printLista(oficial);
	printf("\n");
	printLista(sgt);
	printf("\n");
	printLista(cabo);
	printf("\n");
}

int qtdAtualBarbearia(){
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
		printf("[C:%d|T:%d] ", cursor->categoria, cursor->tempo);
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

nodeCliente_t *shiftHead(nodeCliente_t *head){	
	nodeCliente_t *toDelete;
	
	if(head != NULL){
		toDelete = head;
		head = head->prox;
		free(toDelete);
	}

	return head;
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
