#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>

#include "headers/dealer.h"
#include "headers/preference.h"
#include "headers/resident.h"

int segments[3] = {A_SEG, B_SEG, C_SEG};
int brands[4] = {B1, B2, B3, B4};

int showroomCapacity[4][3] = {{2,2,2}, {2,2,1}, {2,1,1}, {1,1,1}};

Resident residentList[6];
Dealer dealers[4]; // 0: Brand1 Dealer1, 1: Brand2 Dealer2 ...

int main(){
	Resident res1, res2, res3, res4, res5, res6;
	initResident(&res1);
	printResident(&res1);

	initResident(&res2);
	printResident(&res2);

	initResident(&res3);
	printResident(&res3);

	initResident(&res4);
	printResident(&res4);

	initResident(&res5);
	printResident(&res5);

	initResident(&res6);
	printResident(&res6);

	Dealer d1, d2, d3, d4;
	initDealer(&d1, 0);
	initDealer(&d2, 1);
	initDealer(&d3, 2);
	initDealer(&d4, 3);

	printSegmentPrices(&d1);
	printInventory(&d1);

	printSegmentPrices(&d2);
	printInventory(&d2);

	printSegmentPrices(&d3);
	printInventory(&d3);

	printSegmentPrices(&d4);
	printInventory(&d4);



	return EXIT_SUCCESS;
}


