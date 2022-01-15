#include "Potion.h"

Potion::Potion() : Object() {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist4(1, 4);
	typeOfPotion = dist4(rng);
	isOnPlace = false;
}

int Potion::getType() {
	return typeOfPotion;
}

bool Potion::getPlace() {
	return isOnPlace;
}

void Potion::setPlace(bool place) {
	isOnPlace = place;
}

void Potion::move(const std::string& direction) {
	if (direction == "left") {
		sprite.move(-TileSize, 0);
		currentDirection = direction;
	}
	else if (direction == "right") {
		sprite.move(TileSize, 0);
		currentDirection = direction;
	}
	else if (direction == "up") {
		sprite.move(0, -TileSize);
		currentDirection = direction;
	}
	else if (direction == "down") {
		sprite.move(0, TileSize);
		currentDirection = direction;
	}
}

void Potion::undoMove() {

	if (currentDirection == "left") {
		move("right");
	}
	else if (currentDirection == "right") {
		move("left");
	}
	else if (currentDirection == "up") {
		move("down");
	}
	else if (currentDirection == "down") {
		move("up");
	}
}
