#include <stdio.h>
#include <stdlib.h>
#include "headers/resident.h"

int LOAN_AMOUNTS[4] = {200000, 300000, 400000, 500000};

void initResident(Resident* res){
	initPrefList(res->prefList);
	//srand(time(NULL));
	res->loanAmount = LOAN_AMOUNTS[rand() % 4];
}

void printResident(Resident* res){
	printf("Resident Pref List: \n");
	for (int i =0; i < 4; ++i){
		printf("{Brand: %d, ", res->prefList[i].brand);
		printf("Segment: %d}, Remaining Attempts: %d\n", res->prefList[i].segment, res->prefList[i].remainingAttempts);
	}
	printf("Loan Amount: %d\n", res->loanAmount);
	printf("\n");
}

