#include <stdlib.h>
#include <stdio.h>

#include "headers/dealer.h"

//int showroomCapacity[4][3];
//int segments[3];
//int brands[4];


void setInventory(Dealer* d, int brand){
	for (int i = 0; i < 3; ++i){
		d->inventory[i] = showroomCapacity[brand][i];
	}

}

void setSegmentPrices(Dealer* d){
	int lower = 200, upper = 500;
	int i;
	for (i = 0; i < 3; ++i){
		int num = (rand() % (upper - lower + 1)) + lower; // random number between 200-500
		d->priceList[i] = num * 1000;
		lower = num; // higher segment costs higher
	}
}

void initDealer(Dealer* d, int brand){
	setInventory(d, brand);
	setSegmentPrices(d);
}

void printSegmentPrices(Dealer* d){
	for (int i = 0; i < 3; ++i){
		printf("Segment %d: %d\n", segments[i], d->priceList[i]);
	}
	printf("\n");
}

void printInventory(Dealer* d){
	for (int i = 0; i < 3; ++i){
		printf("Segment %d Stock: %d\n", i, d->inventory[i]);
	}
	printf("\n");
}
