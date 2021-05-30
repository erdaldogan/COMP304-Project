#include "headers/dealer.h"

const int factor[2] = {-1, 1}; // used to determine whether to increase or decrease the price

void setInventory(Dealer* d, int brand){
	/* set the inventory of the dealer by reading the showroomCapacity defined in main */
	for (int i = 0; i < 3; ++i){
		d->inventory[i] = showroomCapacity[brand][i];
	}

}

void setSegmentPrices(Dealer* d){
	/* set the initial car prices randomly, in range 200,000 to 500,000 */
	/* prices increase for the higher segment cars */
	int lower = 200, upper = 500;
	int i;
	for (i = 0; i < 3; ++i){
		int num = (rand() % (upper - lower + 1)) + lower; // random number between 200-500
		d->priceList[i] = num * 1000;
		lower = num; // higher segment costs higher
	}
}

void initDealer(Dealer* d, int brand){
	/* initialize the dealer attributes. inventory, prices and brand */
	setInventory(d, brand);
	setSegmentPrices(d);
	d->brand = brands[brand];
}

void printInventory(Dealer* d){
	/* print the inventory of given dealer */
	printf("Dealer %d inventory: ", d->brand);
	printf("Brand: %d {", d->brand);
	for (int i = 0; i < 3; ++i){
		printf("Seg %d, St.: %d Pr.: TL%d; ", i, d->inventory[i], d->priceList[i]);
	}
	printf("}\n");
}

void* updatePrices(void* dealer){
	/* this function runs as a seperate thread */
	/* update the car prices in random intervals, up to 15% */
	Dealer* d = (Dealer *) dealer;
	int direction, currPrice, delta, brand = d->brand;
	float changePercentage;
	while (1){
		sleep(rand() % 4); // sleep for random amount of time, max 3 secs
		direction = factor[rand() % 2]; // -1 or 1, randomly selected
		changePercentage = rand() % 15 / 100.0; // up to 15% increase or decrease 
		//printf("tid: %d, D: %d, P: %.3f\n", (int) pthread_self(), direction, changePercentage);
		if (pthread_mutex_lock(&priceListLock[d->brand]) == 0)
			printf("Dealer: %d; Price Table Price Update Lock Acquired!\n", brand);
		else { fprintf(stderr, "Dealer: %d; Error while acquiring lock!\n", brand); }
		/* critical section */
		for (int i = 0; i < 3; ++i){
			currPrice = d->priceList[i];
			delta = (currPrice * changePercentage) * direction; 
			d->priceList[i] = currPrice + delta;
		}
		/* cs end*/
		if (pthread_mutex_unlock(&priceListLock[d->brand]) == 0)
			printf("Dealer: %d; Price Table Price Update Lock Released!\n", brand);
		else { fprintf(stderr, "Dealer: %d; Error while releasing lock!\n", brand); }
		printInventory(d);
	}
}
