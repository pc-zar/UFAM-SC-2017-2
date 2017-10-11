#include <stdio.h>

typedef struct NodeCliente{
	int categoria;
	int tempo;
	struct NodeCliente *prox;
} nodeCliente_t ;

int main(){
	initFilas();
	return 0;
}

void initFilas(){
	nodeCliente_t *oficial, *sgt, *cabo;
	int i = 0;
	int catTemp = 0;
	int tempoTemp = 0;
	while(i < 100){
		catTemp = rand_range(0, 3);
		switch(catTemp){
			case 1:
				oficial->categoria = catTemp;
				oficial->tempo = rand_range(4, 6);
				break;
			case 2:
				break;
			case 3:
				break;
			case 0:
				break;
		}
		printf("\n");
		i++;
	}	
}

int rand_range(int min_n, int max_n){
	return rand() % (max_n - min_n + 1) + min_n;
}





