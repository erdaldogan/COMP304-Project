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

typedef struct {
	Segment segment;
	Brand brand;
	int remainingAttempts;
} Preference;

typedef struct {
	Preference prefList[4];
	int loanAmount;
} Resident;

Resident residentList[6];

void initResident(Resident* res);
void initPrefList(Preference prefList[4]);
void printResident(Resident* res);

int main(){
	Resident res;
	initResident(&res);
	printResident(&res);	
	return EXIT_SUCCESS;
}

void initResident(Resident* res){
	srand(time(NULL));
	initPrefList(res->prefList);
	res->loanAmount = LOAN_AMOUNTS[rand() % 4];
}

void initPrefList(Preference prefList[4]){
	srand(time(NULL));
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
	printf("Resident:\n");
	printf("Preference List:");
	printf("Resident Pref List: \n");
	for (int i =0; i < 4; ++i){
		printf("{Brand: %d, ", res->prefList[i].brand);
		printf("Segment: %d}, Remaining Attempts: %d\n", res->prefList[i].segment, res->prefList[i].remainingAttempts);
	}
	printf("Loan Amount: %d", res->loanAmount);
}
