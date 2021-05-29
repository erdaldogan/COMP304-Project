#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

#include "headers/dealer.h"
#include "headers/preference.h"
#include "headers/resident.h"

int segments[3] = {A_SEG, B_SEG, C_SEG};
int brands[4] = {B1, B2, B3, B4};

int showroomCapacity[4][3] = {{2,2,2}, {2,2,1}, {2,1,1}, {1,1,1}};

Resident residentList[6];
Dealer dealerList[4]; // 0: Brand1 Dealer1, 1: Brand2 Dealer2 ...

pthread_mutex_t priceListLock[4];
sem_t reprLock[4]; // 2 representatives per dealer
const char sem_names[4] = {'1', '2', '3', '4'};

int main(){
	srand(time(NULL));
	int i;
	for (i = 0; i < 6; i++){
		initResident(&residentList[i]);
	}
	for (i = 0; i < 4; i++){
		initDealer(&dealerList[i], i);
		printSegmentPrices(&dealerList[i]);
		printInventory(&dealerList[i]);
	}

	pthread_t priceUpdateThreads[4]; // threads for update price 
	pthread_t residentThreads[6]; // threads for residents
	pthread_attr_t attr;

	/* get the default attributes*/
	pthread_attr_init(&attr);

	for (i = 0; i < 4; ++i){
		pthread_mutex_init(&priceListLock[i], NULL); // init with default attr
		sem_open(&sem_names[i], O_CREAT, 0644, 2);
		pthread_create(&priceUpdateThreads[i], &attr, updatePrices, &dealerList[i]);
		printf("Created new thread, ID: %d\n",(int) priceUpdateThreads[i]);
	}
	
	for (i = 0; i < 6; ++i){
		pthread_create(&residentThreads[i], &attr, shop, &residentList[i]);
	}
	for (i = 0; i < 6; ++i){
		pthread_join(residentThreads[i], NULL);
	}
	for (i = 0; i < 4; ++i){
		pthread_join(priceUpdateThreads[i], NULL);
	}
	return EXIT_SUCCESS;
}


