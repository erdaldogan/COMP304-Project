#include <stdlib.h>
#include "headers/preference.h"

#define MAX_ATTEMPT 2

void initPrefList(Preference prefList[4]){
	int record[4][3] = {0}; // keep track of preferences to avoid duplicates in prefList
	int randBrand, randSeg; // randomBrand, randomSegment
	for (int i = 0; i < 4; ++i){
		do {
			/* Prevent adding the same (Brand, Segment) combo 
			   to preference list repeatedly*/
			randBrand = rand() % 4;
			prefList[i].brand = brands[randBrand];

			randSeg = rand() % 3;
			prefList[i].segment = segments[randSeg];
		}
		while (record[randBrand][randSeg] != 0); // repeat if the combination is found in records

		record[randBrand][randSeg] = 1; // mark the brand-segment combination 
		prefList[i].remainingAttempts = MAX_ATTEMPT;
	}
}


