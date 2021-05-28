#ifndef RESIDENT_H
#define RESIDENT_H

#include "preference.h"

typedef struct {
	Preference prefList[4];
	int loanAmount;
} Resident;

void initResident(Resident* res);
void printResident(Resident* res);

#endif /* RESIDENT_H */
