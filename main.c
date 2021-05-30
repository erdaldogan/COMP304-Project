#include "headers/dealer.h"
#include "headers/preference.h"
#include "headers/resident.h"

int segments[3] = {A_SEG, B_SEG, C_SEG};
int brands[4] = {B1, B2, B3, B4};

int showroomCapacity[4][3] = {{2,2,2}, {2,2,1}, {2,1,1}, {1,1,1}};

Resident residentList[6];
Dealer dealerList[4]; // 0: Brand1 Dealer1, 1: Brand2 Dealer2 ...

pthread_mutex_t priceListLock[4];
pthread_mutex_t inventoryLock;

sem_t* reprLock[8]; // representative semaphore
const char sem_names[8] = {'1', '2', '3', '4', '5', '6', '7', '8'};

int main(){
	srand(time(NULL));
	int i;
	for (i = 0; i < 6; i++){
		initResident(&residentList[i], i);
	}
	for (int i = 0; i < 4; ++i){	
		initDealer(&dealerList[i], i);
		printInventory(&dealerList[i]);
	}

	pthread_t priceUpdateThreads[4]; // threads for dealer to update price 
	pthread_t residentThreads[6]; // threads for residents
	pthread_attr_t attr;

	/* get the default attributes*/
	pthread_attr_init(&attr);
	pthread_mutex_init(&inventoryLock, NULL);

	for (i = 0; i < 8; ++i){
		reprLock[i] = sem_open(&sem_names[i], O_CREAT, 0644, 1); // 2 representative per dealer
	}
	for (i = 0; i < 4; ++i){
		pthread_mutex_init(&priceListLock[i], NULL); // init with default attr
		pthread_create(&priceUpdateThreads[i], &attr, updatePrices, &dealerList[i]);
	}

	for (i = 0; i < 6; ++i){
		pthread_create(&residentThreads[i], &attr, shop, &residentList[i]);
	}
	for (i = 0; i < 6; ++i){
		pthread_join(residentThreads[i], NULL);
	}
	printf("\n\n** Resident threads terminated (joined) successfully **\n");
	printf("** Dealer price update threads are being terminated... **\n");
	for (i = 0; i < 4; ++i){
		if (pthread_cancel(priceUpdateThreads[i]) == 0)
			printf("Dealer %d thread termination success\n", i);
	}
	return EXIT_SUCCESS;
}


