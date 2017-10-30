#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_CLIENTES 25
#define MAX_BARBEARIA 20
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
void *tenenteEscovinha();
nodeCliente_t *shiftHead(nodeCliente_t *head);
void barbeiroPercorre();

int main(void){
	srand(time(NULL));
	filaEspera = initFilaEspera();
	int inputQtdSleepTainha = 0;
	int qtdSleepTainhaLock = 1;
	pthread_t tSgtTainha, tRecrutaZero, tTenenteEscovinha;
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
	pthread_create(&tTenenteEscovinha, NULL, tenenteEscovinha, NULL);	

	pthread_join(tSgtTainha, NULL);
	pthread_join(tRecrutaZero, NULL);
	pthread_join(tTenenteEscovinha, NULL);
	
	sem_destroy(&semOficial);
	sem_destroy(&semSgt);
	sem_destroy(&semCabo);

	return 0;
}

void *tenenteEscovinha(){
	float barbeariaPerc = 0;
	float barbeariaPercLivre = 0;

	while(qtdAtualBarbearia() != 0){
		
		barbeariaPerc = ((float) qtdAtualBarbearia()) / MAX_BARBEARIA;
		barbeariaPerc = barbeariaPerc * 100;
		
		barbeariaPercLivre = 100 - barbeariaPerc;

		//printf("%d\n", qtdAtualBarbearia());
		printf("%.f%% LIVRE!\n", barbeariaPercLivre);
		sleep(3);
	}

	return NULL;
}

void barbeiroPercorre(){
	nodeCliente_t *cursor = oficial;
	//primeiro remocao de oficiais
	while(cursor != NULL){
		int tempo = cursor->tempo;
		sem_wait(&semOficial);
			sleep(tempo);
			//printf("R0: REMOCAO em Oficial | DURACAO: %d\n", tempo);
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
		//printf("R0: REMOCAO EM Sgt | DURACAO: %d\n", tempo);
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
		//printf("R0: REMOCAO EM cabo | DURACAO: %d\n", tempo);
		cabo = shiftHead(cabo);
		sem_post(&semCabo);
		cursor = cabo;
	}
}

void *recrutaZero(){
	while(qtdPausas != 3){
		barbeiroPercorre();
	}

	//verificar se a barbearia ainda possui clientes apos o fim da thread do sgt tainha
	if(qtdAtualBarbearia() != 0){
		//printf("BARBEARIA AINDA POSSUI CLIENTES!! REEXCUTAR BARBEIRO PARA ULTIMA VERIFICACAO\n");
		while(qtdAtualBarbearia() != 0){
			barbeiroPercorre();
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
						//printf("INSERCAO EM OFICIAL!!!! | DURACAO: %d\n", cursor->tempo);
						oficial = appendNodeCliente(oficial, 1, cursor->tempo);	
						sem_post(&semOficial);
						break;
					case 2:
						sem_wait(&semSgt);
						//printf("INSERCAO EM SGT!!! | DURACAO: %d\n", cursor->tempo);
						sgt = appendNodeCliente(sgt, 2, cursor->tempo);	
						sem_post(&semSgt);
						break;
					case 3:
						sem_wait(&semCabo);
						//printf("INSERCAO EM CABO!!! | DURACAO: %d\n", cursor->tempo);
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
		cursor = cursor->prox;
		sleep(qtdSleepTainha);
	}
	//printf("SGT TAINHA TERMINOU SUA EXECUCAO\n");
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
