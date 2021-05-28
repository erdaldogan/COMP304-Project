#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#include "headers/dealer.h"

const int factor[2] = {-1, 1};

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
	d->brand = brands[brand];
}

void printSegmentPrices(Dealer* d){
//	printf("\nDealer of brand  %d\n", d->brand);
	for (int i = 0; i < 3; ++i){
		printf("Seg %d: TL%d ", segments[i], d->priceList[i]);
	}
}

void printInventory(Dealer* d){
	for (int i = 0; i < 3; ++i){
		printf("Seg %d, Stck: %d; ", i, d->inventory[i]);
	}
	printf("\n");
}

void* updatePrices(void* dealer){
	Dealer* d = (Dealer *) dealer;
	int direction, currPrice, delta;
	float changePercentage;
	while (1){
		printf("Before\n");
		printSegmentPrices(d);
		sleep(2);
		direction = factor[rand() % 2]; // -1 or 1, randomly selected
		changePercentage = rand() % 15 / 100.0; // up to 15% increase or decrease 
		printf("tid: %d, D: %d, P: %.3f\n", (int) pthread_self(), direction, changePercentage);
		for (int i = 0; i < 3; ++i){
			currPrice = d->priceList[i];
			delta = (currPrice * changePercentage) * direction; 
			d->priceList[i] = currPrice + delta;
		}
		printf("After\n");
		printSegmentPrices(d);
		printf("\n\n\n");

	}
}
