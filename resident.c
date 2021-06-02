#include <errno.h>
#include <string.h>
#include "headers/resident.h"

int LOAN_AMOUNTS[4] = {200000, 300000, 400000, 500000};

void initResident(Resident* res, int id){
	/* initialize the resident */
	res->id = id;
	initPrefList(res->prefList);
	res->loanAmount = LOAN_AMOUNTS[rand() % 4]; // choosen randomly among the options
	printf("Resident %d initiated ", id);
	printf("PL: {"); // Preference List
	for (int i = 0; i< 4; ++i){
		printf("B: %d, S: %d ", res->prefList[i].brand, res->prefList[i].segment);
	}
	printf("}. LA: %d\n", res->loanAmount);
}

void printResident(Resident* res){
	/* print the resident and it's attributes */
	printf("Resident %d:\n", res->id);
	printf("Pref List: \n");
	for (int i =0; i < 4; ++i){
		printf("{Brand: %d, ", res->prefList[i].brand);
		printf("Segment: %d}, Remaining Attempts: %d\n", res->prefList[i].segment, res->prefList[i].remainingAttempts);
	}
	printf("Loan Amount: %d\n", res->loanAmount);
	printf("\n");
}

void* shop(void* resident){
	Resident* r = (Resident*) resident;
	int i, inventory, price, reprLockIdx, rid = r->id;
	Brand prefBrand;
	Segment prefSegment;
	Preference currPref; // current preference
	int reprNo;
	for (i = 0; i < 4; ++i){
		while ((currPref = r->prefList[i]).remainingAttempts > 0){	
			prefBrand = currPref.brand;
			prefSegment = currPref.segment;
			reprLockIdx = prefBrand * 2;
			while (1 == 1){
				if (sem_trywait(reprLock[reprLockIdx]) == 0){
					reprNo = 1;
					break;
				}
				else if (sem_trywait(reprLock[reprLockIdx + 1]) == 0){
					reprNo = 2;
					break;
				}
			}	
			printf("Resident: %d; Semaphore acquired for representative %d of brand %d, segment %d\n", rid, reprNo, prefBrand, prefSegment);
			pthread_mutex_lock(&inventoryLock);
			pthread_mutex_lock(&priceListLock[prefBrand]);
			/* critical segment */
			inventory = showroomCapacity[prefBrand][prefSegment];
			price = dealerList[prefBrand].priceList[prefSegment];
			if (inventory <= 0){
				printf("Resident: %d, Failed attempt to buy. (Out of stock!)\n", rid);
			}
			else if (r->loanAmount < price){
				printf("Resident: %d, Failed attempt to buy. (Cannot afford!) Loan Amt.: %d, Price: %d\n",
						rid, r->loanAmount, price);

			}
			else {
				showroomCapacity[prefBrand][prefSegment]--;
				printf("Resident: %d; Resident bought Brand %d, Segment %d for TL%d\n", rid, prefBrand, prefSegment, price);
				pthread_mutex_unlock(&inventoryLock);
				pthread_mutex_unlock(&priceListLock[prefBrand]);
				if (reprNo == 1)
					sem_post(reprLock[reprLockIdx]);
				else
					sem_post(reprLock[reprLockIdx + 1]);
				printf("Resident: %d; Semaphore released for representative %d of brand %d\n", rid, reprNo, prefBrand);
				printf("Resident: %d; Success! Exiting Thread\n", rid);
				pthread_exit(0);
			}
			pthread_mutex_unlock(&priceListLock[prefBrand]);
			pthread_mutex_unlock(&inventoryLock);
			printf("Resident: %d; Semaphore released for representative %d of brand %d\n", rid, reprNo, prefBrand);
			if (reprNo == 1)
				sem_post(reprLock[reprLockIdx]);
			else
				sem_post(reprLock[reprLockIdx + 1]);
			/* cs end */
			r->prefList[i].remainingAttempts--; // decrease the remaining attempts;
			sleep(rand() % 4);
		}
		sleep(5);
	}
	pthread_exit(0);
}
