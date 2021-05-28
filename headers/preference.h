#ifndef PREF_H
#define PREF_H

#include "enums.h"

extern int segments[3];
extern int brands[4];

typedef struct {
	Segment segment;
	Brand brand;
	int remainingAttempts;
} Preference;

void initPrefList(Preference prefList[4]);

#endif /* PREF_H */
