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
int tempoTotalAtendimentoOficial;
int tempoTotalAtendimentoSgt;
int tempoTotalAtendimentoCabo;
int qtdAtenOficial;
int qtdAtenSgt;
int qtdAtenCabo;
int lockTainha;

//BARBEARIA
nodeCliente_t *filaEspera, *oficial, *sgt, *cabo;

//prototypes
nodeCliente_t *initFilaEspera();
void printLista(nodeCliente_t *head);
nodeCliente_t *appendNodeCliente(nodeCliente_t *head, int catTemp, int tempoTemp);
nodeCliente_t *criaNode();
int sizeFila(nodeCliente_t *head);
int qtdAtualBarbearia();
void printBarbearia();
int rand_range(int min_n, int max_n);
void *sgtTainha();
void *recrutaZero();
void *dentinho();
void *tenenteEscovinha();
nodeCliente_t *shiftHead(nodeCliente_t *head);
void barbeiroPercorre();
void removeOficial();
void removeSgt();
void removeCabo();

int main(void){
	srand(time(NULL));
	filaEspera = initFilaEspera();
	int inputQtdSleepTainha = 0;
	int qtdSleepTainhaLock = 1;
	qtdAtenOficial = 0;
	qtdAtenSgt = 0;
	qtdAtenCabo = 0;

	pthread_t tSgtTainha, tRecrutaZero, tDentinho, tTenenteEscovinha;
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
	
	lockTainha = 0;
	sem_init(&semOficial, 0, 1);
	sem_init(&semSgt, 0, 1);
	sem_init(&semCabo, 0, 1);

	pthread_create(&tSgtTainha, NULL, sgtTainha, NULL);	
	pthread_create(&tRecrutaZero, NULL, recrutaZero, NULL);	
	//pthread_create(&tDentinho, NULL, dentinho, NULL);	
	pthread_create(&tTenenteEscovinha, NULL, tenenteEscovinha, NULL);	

	pthread_join(tSgtTainha, NULL);
	pthread_join(tRecrutaZero, NULL);
	//pthread_join(tDentinho, NULL);
	pthread_join(tTenenteEscovinha, NULL);
	
	sem_destroy(&semOficial);
	sem_destroy(&semSgt);
	sem_destroy(&semCabo);

	return 0;
}

int printEstadoAtual(){
	float barbeariaPerc = 0;
	float oficialPerc = 0;
	float sgtPerc = 0;
	float caboPerc = 0;
	float barbeariaPercLivre = 0;
	
	barbeariaPerc = ((float) qtdAtualBarbearia()) / MAX_BARBEARIA;
	oficialPerc = ((float) sizeFila(oficial)) / MAX_BARBEARIA;
	sgtPerc = ((float) sizeFila(sgt)) / MAX_BARBEARIA;
	caboPerc = ((float) sizeFila(cabo)) / MAX_BARBEARIA;
	
	barbeariaPerc = barbeariaPerc * 100;
	oficialPerc = oficialPerc * 100;
	sgtPerc = sgtPerc * 100;
	caboPerc = caboPerc * 100;
	barbeariaPercLivre = 100 - barbeariaPerc;
	printf("OFICIAL (%.f%%) | SGT (%.f%%) | CABO(%.f%%) | %.f%% LIVRE\n", oficialPerc, sgtPerc, caboPerc, barbeariaPercLivre);
	printf("\n");
	printBarbearia();
	printf("\n");

	if(barbeariaPerc == 0){
		return 1;
	}

	return 0;
}

void *tenenteEscovinha(){
	int t = 0;
	int ot = 0;
	int st = 0;
	int ct = 0;
	int tamanhoOficialTotal = 0;
	int tamanhoSgtTotal = 0;
	int tamanhoCaboTotal = 0;
	
	while((qtdAtualBarbearia() != 0) || (qtdPausas != 3)){
		printEstadoAtual();
		sleep(1);	
	}

	printf("\nFIM DO DIA!\n");

	float oficialAvgComp = ((float) tamanhoOficialTotal) / (t - ot);
	float sgtAvgComp = ((float) tamanhoSgtTotal) / (t - st);
	float caboAvgComp = ((float) tamanhoCaboTotal) / (t - ct);
	
	float oficialAvgAten = ((float) tempoTotalAtendimentoOficial) / (t - ot);
	float sgtAvgAten = ((float) tempoTotalAtendimentoSgt) / (t - st);
	float caboAvgAten = ((float) tempoTotalAtendimentoCabo) / (t - ct);
	

	printf("COMPRIMENTO MEDIO: \n");
	printf("oficial = %f | sgt = %f | cabo = %f", oficialAvgComp, sgtAvgComp, caboAvgComp);
	printf("\nTEMPO MEDIO ATENDIMENTO: \n");
	printf("oficial = %f | sgt = %f | cabo = %f", oficialAvgAten, sgtAvgAten, caboAvgAten);
	printf("\nQTD DE ATENDIMENTOS POR CATEGORIA:\n");
	printf("oficial = %d | sgt = %d | cabo = %d\n", qtdAtenOficial, qtdAtenSgt, qtdAtenCabo);

	return NULL;
}

void removeOficial(){
	nodeCliente_t *cursor = oficial;
	//primeiro remocao de oficiais
	while(cursor != NULL){
		int tempo = cursor->tempo;
		tempoTotalAtendimentoOficial += tempo;
		sem_wait(&semOficial);
		sleep(tempo);
		//printf("R0: REMOCAO em Oficial | DURACAO: %d\n", tempo);
		oficial = shiftHead(oficial);
		qtdAtenOficial = qtdAtenOficial + 1; 
		sem_post(&semOficial);
		cursor = oficial;
	}
}

void removeSgt(){
	nodeCliente_t *cursor = sgt;
	while(cursor != NULL){
		if(oficial == NULL){
			removeOficial();
		}
		int tempo = cursor->tempo;
		tempoTotalAtendimentoSgt += tempo;
		sem_wait(&semSgt);
		sleep(tempo);
		//printf("R0: REMOCAO em Oficial | DURACAO: %d\n", tempo);
		sgt = shiftHead(sgt);
		qtdAtenSgt++;
		sem_post(&semSgt);
		cursor = sgt;
	}
}

void removeCabo(){
	nodeCliente_t *cursor = cabo;
	while(cursor != NULL){
		/*if(oficial != NULL){
			removeOficial();
		}*/
		if(sgt != NULL){
			removeSgt();
		}
		int tempo = cursor->tempo;
		tempoTotalAtendimentoCabo += tempo;
		sem_wait(&semCabo);
		sleep(tempo);
		cabo = shiftHead(cabo);
		qtdAtenCabo++;
		sem_post(&semCabo);
		cursor = cabo;
	}
	
	/*if(oficial != NULL){
		removeOficial();
	}
	if(sgt != NULL){
		removeSgt();
	}*/
	
}

void barbeiroPercorre(){
	removeOficial();
	removeSgt();
	removeCabo();
}

void *recrutaZero(){
	while(1 == 1){
		barbeiroPercorre();
	}

	pthread_exit(NULL);	
	return NULL;	
}

void *dentinho(){
}

void *sgtTainha(){
	qtdPausas = 0;
	nodeCliente_t *cursor;
	cursor = filaEspera;
	
	while((cursor != NULL) && (qtdPausas != 3)){
		if(cursor->categoria != 0){
			qtdPausas = 0;
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
	printf("SGT TAINHA TERMINOU SUA EXECUCAO\n");
	lockTainha = 1;
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

int sizeFila(nodeCliente_t *head){
	int qtd = 0;
	nodeCliente_t *cursor = head;

	while(cursor != NULL){
		qtd++;
		cursor = cursor->prox;
	}

	return qtd;

}

int qtdAtualBarbearia(){
	int qtdTotal = 0;
	return qtdTotal = sizeFila(oficial) + sizeFila(sgt) + sizeFila(cabo);
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
