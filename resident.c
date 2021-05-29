#include "headers/resident.h"

int LOAN_AMOUNTS[4] = {200000, 300000, 400000, 500000};

void initResident(Resident* res){
	/* initialize the resident */
	initPrefList(res->prefList);
	res->loanAmount = LOAN_AMOUNTS[rand() % 4]; // choosen randomly among the options
	printf("New resident initiated. ");
	printf("PL: {"); // Preference List
	for (int i = 0; i< 4; ++i){
		printf("B: %d, S: %d ", res->prefList[i].brand, res->prefList[i].segment);
	}
	printf("}. LA: %d\n", res->loanAmount);
}

void printResident(Resident* res){
	/* print the resident and it's attributes */
	printf("Resident:\n");
	printf("Pref List: \n");
	for (int i =0; i < 4; ++i){
		printf("{Brand: %d, ", res->prefList[i].brand);
		printf("Segment: %d}, Remaining Attempts: %d\n", res->prefList[i].segment, res->prefList[i].remainingAttempts);
	}
	printf("Loan Amount: %d\n", res->loanAmount);
	printf("\n");
}

void* shop(void* resident){
	Resident* r = (Resident*) resident;
	int i, inventory, price, tid = (int) pthread_self();
	Brand prefBrand;
	Segment prefSegment;
	Preference currPref; // current preference
	for (i = 0; i < 4; ++i){
		while ((currPref = r->prefList[i]).remainingAttempts > 0){	
			prefBrand = currPref.brand;
			prefSegment = currPref.segment;

			sem_wait(&reprLock[prefBrand]);
			printf("TID: %d; Semaphore Acquired for brand %d\n", tid, prefBrand);
			pthread_mutex_lock(&priceListLock[prefBrand]);
			pthread_mutex_lock(&inventoryLock);

			inventory = showroomCapacity[prefBrand][prefSegment];
			price = dealerList[prefBrand].priceList[prefSegment];

			if (inventory > 0 && r->loanAmount >= price){
				showroomCapacity[prefBrand][prefSegment]--;
				printf("TID: %d; Resident bought Brand %d, Segment %d\n", tid, prefBrand, prefSegment);
				pthread_mutex_unlock(&inventoryLock);
				pthread_mutex_unlock(&priceListLock[prefBrand]);
				sem_post(&reprLock[prefBrand]);
				printf("TID: %d; Success! Exiting Thread\n", tid);
				pthread_exit(0);
			}
			pthread_mutex_unlock(&inventoryLock);	
			pthread_mutex_unlock(&priceListLock[prefBrand]);
			sem_post(&reprLock[prefBrand]);
			r->prefList[i].remainingAttempts--; // decrease the remaining attempts;
			printf("TID: %d; Failed attempt to buy; B: %d, S: %d, Remained: %d\n",
			tid, prefBrand, prefSegment, r->prefList[i].remainingAttempts);
			printf("TID: %d; Semaphore released for brand %d\n", tid, prefBrand);
			sleep(rand() % 4);
		}
	}
	pthread_exit(0);
}
