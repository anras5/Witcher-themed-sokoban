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

void FinishPoint::setPicture() {
	switch (getState()) {
	case 0:
		Object::setPicture("pictures/table.png");
		break;
	case 1:
		Object::setPicture("pictures/table_green.png");
		break;
	case 2:
		Object::setPicture("pictures/table_red.png");
		break;
	case 3:
		Object::setPicture("pictures/table_violet.png");
		break;
	case 4:
		Object::setPicture("pictures/table_yellow.png");
		break;
	}
}

