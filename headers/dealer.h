#ifndef DEALER_H
#define DEALER_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

#include "enums.h"

extern int showroomCapacity[4][3];
extern int segments[3];
extern int brands[4];

extern pthread_mutex_t priceListLock[4];
extern sem_t reprLock[4];

typedef struct {
	int inventory[3]; // 0: A-Segment, 1: B-Segment, 2: C-Segment
	int priceList[3]; // 0: A-Segment Price, 1: B-Segment Price, 2: C-Segment Price
	Brand brand;
} Dealer; 


void setSegmentPrices(Dealer* d);
void printInventory(Dealer* d);
void initDealer(Dealer *d, int brand);
void* updatePrices(void *d);

#endif /* DEALER_H */
