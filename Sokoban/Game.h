#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Block.h"
#include "Player.h"
#include "Potion.h"
#include "FinishPoint.h"

class Game
{
public:
	Game();
	~Game() = default;
	void Menu();
private:

	bool isPlaying;
	const int TileSize = 64;

	Player player;
	std::vector<Block> blocks;
	std::vector<Potion> potions;
	std::vector<FinishPoint> finishPoints;

	sf::RenderWindow window;
	sf::Font font;

	void about();

	void startGame();
	int startLevel(std::string levelFilePath);
	void uploadBoard(std::string levelFilePath);
	void processEvents(bool* RESET);
	void reset();
	void updateBoard();
	void detectCollisions();
	void detectFinishPoints();
	void detectEndGame(bool *isLevelFinished);
};

