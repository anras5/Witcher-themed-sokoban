#include "FinishPoint.h"

FinishPoint::FinishPoint() : Object() {
	isFull = 0;
}

int FinishPoint::getState() {
	return isFull;
}

void FinishPoint::setState(int state) {
	isFull = state;
}

