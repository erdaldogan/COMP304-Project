#ifndef RESIDENT_H
#define RESIDENT_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#include <pthread.h>
#include "preference.h"
#include "dealer.h"

extern int showroomCapacity[4][3];
extern sem_t* reprLock[8];
extern pthread_mutex_t inventoryLock;
extern pthread_mutex_t priceListLock[4];
extern Dealer dealerList[4];

typedef struct {
	Preference prefList[4];
	int loanAmount;
	int id;
} Resident;

void initResident(Resident* res, int id);
void printResident(Resident* res);
void* shop(void* resident);
#endif /* RESIDENT_H */

