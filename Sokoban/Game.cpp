#include <fstream>
#include <iostream>
#include "Game.h"
using namespace std;


Game::Game() : window(sf::VideoMode{ 800, 600 }, "Witcher 4", sf::Style::Close | sf::Style::Titlebar), player() {
	window.setFramerateLimit(60);
	isPlaying = true;
}

void Game::Menu() {
	startLevel("level3.txt");
}

void Game::startLevel(std::string levelFilePath) {
	bool RESET = false;
	bool isLevelFinished = false;
	uploadBoard(levelFilePath);
	while (isPlaying && !isLevelFinished) {
		processEvents(RESET);
		if (isPlaying) {
			window.clear(sf::Color{ 160, 160, 160 });
			detectCollisions();
			detectFinishPoints();
			updateBoard();
			window.display();
		}
		detectEndGame();
		if (RESET == true) {
			reset();
			uploadBoard(levelFilePath);
			RESET = false;
		}
	}
	window.close();
}

void Game::reset() {
	potions.clear();
	blocks.clear();
	finishPoints.clear();
}

void Game::processEvents(bool RESET) {

	sf::Event event;
	window.pollEvent(event);
	if (event.type == sf::Event::Closed) {
		isPlaying = false;
	}
	else if (event.type == sf::Event::KeyPressed) {
		cout << "key pressed" << endl;
		switch (event.key.code) {
			case sf::Keyboard::Left:
				player.move("left");
				break;
			case sf::Keyboard::Right:
				player.move("right");
				break;
			case sf::Keyboard::Up:
				player.move("up");
				break;
			case sf::Keyboard::Down:
				player.move("down");
				break;
			case sf::Keyboard::R:
				RESET = true;
				break;
		}
	}
}

void Game::uploadBoard(std::string levelFilePath) {
	std::ifstream file(levelFilePath);
	int x, y, temp;
	file >> x >> y;
	player.setPosition(x * TileSize, y * TileSize);
	x = 0;
	y = 0;
	while (!file.eof()) {
		file >> temp;
		if (temp == 1) {
			Block block;
			block.setPosition(x * TileSize, y * TileSize);
			blocks.emplace_back(block);
		}
		else if (temp == 2) {
			Potion potion;
			potion.setPosition(x * TileSize, y * TileSize);
			potions.emplace_back(potion);
		}
		else if (temp == 3) {
			FinishPoint finishPoint;
			finishPoint.setPosition(x * TileSize, y * TileSize);
			finishPoints.emplace_back(finishPoint);
		}
		x++;
		if (file.peek() == '\n') {
			x = 0;
			y++;
		}
	}
}

void Game::detectCollisions() {
	// collision player-block
	for (auto& block : blocks) {
		if (block.getPosition() == player.getPosition()) {
			player.undoMove();
		}
	}
	//potion collision
	for (std::vector<int>::size_type i = 0; i != potions.size(); i++) {
		if (potions[i].getPosition() == player.getPosition()) {
			potions[i].move(player.getCurrentDirection());
			//collision potion(not in place)-block
			for (std::vector<int>::size_type j = 0; j != blocks.size(); j++) {
				if (potions[i].getPosition() == blocks[j].getPosition()) {
					potions[i].undoMove();
					player.undoMove();
					break;
				}
			}
			//collision potion(not in place)-potion
			for (std::vector<int>::size_type j = 0; j != potions.size(); j++) {
				if (i != j) {
					if (potions[i].getPosition() == potions[j].getPosition()) {
						potions[i].undoMove();
						player.undoMove();
						break;
					}
				}
			}
			potions[i].setPlace(false);
		}
	}
}

void Game::detectFinishPoints() {
	for (auto& finishPoint : finishPoints) {
		bool found = false;
		for (auto& potion : potions) {
			if (finishPoint.getPosition() == potion.getPosition()) {
				potion.setPlace(true);
				finishPoint.setState(potion.getType());
				found = true;
			}
		}
		if (!found) {
			finishPoint.setState(0);
		}
	}
}

void Game::detectEndGame() {
	int howManyPotionsOnPlace = 0;
	for (auto& finishPoint : finishPoints) {
		for (auto& potion : potions) {
			if (finishPoint.getPosition() == potion.getPosition()) {
				howManyPotionsOnPlace++;
				break;
			}
		}
	}
	if (howManyPotionsOnPlace == finishPoints.size()) {
		isPlaying = false;
	}
	//cout << howManyPotionsOnPlace << " " << finishPoints.size() << endl;

}

void Game::updateBoard() {
	//cout << player.getPosition().x << " " << player.getPosition().y << endl;

	for (auto& block : blocks) {
		block.setPicture("pictures/block.png");
		window.draw(block);
	}

	for (auto& finishPoint : finishPoints) {
		switch (finishPoint.getState()) {
		case 0:
			finishPoint.setPicture("pictures/table.png");
			break;
		case 1:
			finishPoint.setPicture("pictures/table_green.png");
			break;
		case 2:
			finishPoint.setPicture("pictures/table_red.png");
			break;
		case 3:
			finishPoint.setPicture("pictures/table_violet.png");
			break;
		case 4:
			finishPoint.setPicture("pictures/table_yellow.png");
			break;
		}
		window.draw(finishPoint);
	}

	for (auto& potion : potions) {
		switch (potion.getType()) {
		case 1:
			potion.getPlace() ? potion.setPicture("pictures/none.png") : potion.setPicture("pictures/potion_green.png");
			break;
		case 2:
			potion.getPlace() ? potion.setPicture("pictures/none.png") : potion.setPicture("pictures/potion_red.png");
			break;
		case 3:
			potion.getPlace() ? potion.setPicture("pictures/none.png") : potion.setPicture("pictures/potion_violet.png");
			break;
		case 4:
			potion.getPlace() ? potion.setPicture("pictures/none.png") : potion.setPicture("pictures/potion_yellow.png");
			break;
		default:
			potion.getPlace() ? potion.setPicture("pictures/none.png") : potion.setPicture("pictures/potion_red.png");
			break;
		}
		window.draw(potion);
	}

	window.draw(player);
}
