#ifndef RESIDENT_H
#define RESIDENT_H

#include <semaphore.h>
#include "preference.h"

extern sem_t reprLock[4];

typedef struct {
	Preference prefList[4];
	int loanAmount;
} Resident;

void initResident(Resident* res);
void printResident(Resident* res);
void* shop(void* resident);

#endif /* RESIDENT_H */


