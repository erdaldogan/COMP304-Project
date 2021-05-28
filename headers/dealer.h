#ifndef DEALER_H
#define DEALER_H

extern int showroomCapacity[4][3];
extern int segments[3];
extern int brands[4];


typedef struct {
	int inventory[3]; // 0: A-Segment, 1: B-Segment, 2: C-Segment
	int priceList[3]; // 0: A-Segment Price, 1: B-Segment Price, 2: C-Segment Price

} Dealer; 


void setSegmentPrices(Dealer* d);
void printSegmentPrices(Dealer* d);
void printInventory(Dealer* d);
void initDealer(Dealer *d, int brand);

#endif /* DEALER_H */
