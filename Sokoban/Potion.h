#pragma once
#include <random>
#include "Object.h"

class Potion : public Object
{
private:
	int typeOfPotion;
	bool isOnPlace;
	std::string currentDirection;
public:
	Potion();
	int getType();
	bool getPlace();
	void setPlace(bool place);
	void move(const std::string& direction);
	void undoMove();
};

