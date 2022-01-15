#pragma once
#include "Object.h"
#include "Potion.h"

class FinishPoint : public Object
{
private:
	int isFull;
public:
	FinishPoint();
	int getState();
	void setState(int state);
};

