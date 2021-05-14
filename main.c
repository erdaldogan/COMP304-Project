#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<semaphore.h>
#include<pthread.h>
#include<time.h>

#define MAX_ATTEMPT 2

int LOAN_AMOUNTS[4] = {200000, 300000, 400000, 500000};

typedef enum {A_SEG, B_SEG, C_SEG} Segment;
typedef enum {B1, B2, B3, B4} Brand;

int segments[3] = {A_SEG, B_SEG, C_SEG};
int brands[4] = {B1, B2, B3, B4};

int showroomCapacity[4][3] = {{2,2,2}, {2,2,1}, {2,1,1}, {1,1,1}};

typedef struct {
	Segment segment;
	Brand brand;
	int remainingAttempts;
} Preference;

typedef struct {
	Preference prefList[4];
	int loanAmount;
} Resident;

typedef struct {
	int inventory[3]; // 0: A-Segment, 1: B-Segment, 2: C-Segment
	int priceList[3]; // 0: A-Segment Price, 1: B-Segment Price, 2: C-Segment Price

} Dealer;

Resident residentList[6];
Dealer dealers[4]; // 0: Brand1 Dealer1, 1: Brand2 Dealer2 ...

void initResident(Resident* res);
void initPrefList(Preference prefList[4]);
void printResident(Resident* res);
void setSegmentPrices(Dealer* d);
void printSegmentPrices(Dealer* d);
void printInventory(Dealer* d);
void initDealer(Dealer *d, int brand);

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

void initResident(Resident* res){
	initPrefList(res->prefList);
	//srand(time(NULL));
	res->loanAmount = LOAN_AMOUNTS[rand() % 4];
}

void initPrefList(Preference prefList[4]){
	//srand(time(NULL));
	int record[4][3] = {0};
	int randBrand, randSeg;
	for (int i = 0; i < 4; ++i){
		do {
		/* Prevent adding the same (Brand, Segment) combo 
		to preference list repeatedly*/
		randBrand = rand() % 4;
		prefList[i].brand = brands[randBrand];
		
		randSeg = rand() % 3;
		prefList[i].segment = segments[randSeg];
		}
		while (record[randBrand][randSeg] != 0);

		record[randBrand][randSeg] = 1;
		prefList[i].remainingAttempts = MAX_ATTEMPT;
	}
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

void setInventory(Dealer* d, int brand){
	for (int i = 0; i < 3; ++i){
		d->inventory[i] = showroomCapacity[brand][i];
	}
	
}

void setSegmentPrices(Dealer* d){
//	srand(time(NULL));
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
