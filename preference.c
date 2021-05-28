#include <stdlib.h>
#include "headers/preference.h"

#define MAX_ATTEMPT 2

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


