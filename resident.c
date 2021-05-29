#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
	int i;
	Brand prefBrand;
	Preference currPref; // current preference
	for (i = 0; i < 4; ++i){
		while ((currPref = r->prefList[i]).remainingAttempts > 0){	
			prefBrand = currPref.brand;
			sem_wait(&reprLock[prefBrand]);
			printf("Semaphore Acquired for brand %d\n", prefBrand);
			sem_post(&reprLock[prefBrand]);
			r->prefList[i].remainingAttempts--; // decrease the remaining attempts;
			printf("Semaphore released for brand %d\n", prefBrand);

		}

	}
}
