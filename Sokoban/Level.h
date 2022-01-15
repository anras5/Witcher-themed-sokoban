#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Block.h"
#include "Player.h"
#include "Potion.h"
#include "FinishPoint.h"

class Level
{
public:
	Level();
	void startLevel();
private:

	bool RESET, isLevelFinished;
	const int TileSize = 64;

	Player player;
	std::vector<Block> blocks;
	std::vector<Potion> potions;
	std::vector<FinishPoint> finishPoints;

	void uploadBoard();
	void reset();
	void processEvents();
	void detectCollisions();
	void detectFinishPoints();
	void detectEndGame();
	void updateBoard();
};

