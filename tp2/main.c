#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_CLIENTE 25

sem_t waitingRoom;

int main(){
	printf("Hello World");
	return 0;
}
