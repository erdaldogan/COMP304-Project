#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

	pthread_t update_tid[4]; // update price threads
	pthread_attr_t attr;

	/* get the default attributes*/
	pthread_attr_init(&attr);
	for (i = 0; i < 4; ++i){
		pthread_create(&update_tid[i], &attr, updatePrices, &dealerList[i]);
		printf("Created new thread, ID: %d\n",(int) update_tid[i]);
	}
	for (i = 0; i < 4; ++i){
		pthread_join(update_tid[i], NULL);
	}
	return EXIT_SUCCESS;
}


