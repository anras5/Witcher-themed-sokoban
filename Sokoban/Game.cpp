#include <fstream>
#include <iostream>
#include "Game.h"
using namespace std;


Game::Game() : window(sf::VideoMode{ 576, 576 }, "Witcher 4", sf::Style::Close | sf::Style::Titlebar), player() {
	window.setFramerateLimit(60);
	font.loadFromFile("fonts/LuxuriousRoman-Regular.ttf");
	isPlaying = true;
}

void Game::Menu() {
	Button logo(288, 75, 300, 150, &font, "WITCHER 4", 35, sf::Color{ 150, 120, 30 }, sf::Color{ 120, 120, 120 }, sf::Color{ 0, 230, 230 });
	Button playButton(288, 250, 200, 100, &font, "PLAY", 20, sf::Color{ 150, 120, 30 }, sf::Color{ 120, 120, 120 }, sf::Color{0, 230, 230});
	Button aboutButton(288, 375, 200, 100, &font, "ABOUT", 20, sf::Color{ 150, 120, 30 }, sf::Color{ 120, 120, 120 }, sf::Color{ 0, 230, 230 });
	Button exitButton(288, 500, 200, 100, &font, "EXIT", 20, sf::Color{ 150, 120, 30 }, sf::Color{ 120, 120, 120 }, sf::Color{ 0, 230, 230 });
	int indicator = 0; // 0 - play, 1 - about, 2 - exit
	bool PLAY = false;
	bool ABOUT = false;
	bool EXIT = false;
	while (!PLAY && !ABOUT && !EXIT) {
		window.clear(sf::Color{ 160, 160, 160 });
		switch (indicator)
		{
		case 0:
			playButton.setHoverState();
			aboutButton.setIdleState();
			exitButton.setIdleState();
			break;
		case 1:
			playButton.setIdleState();
			aboutButton.setHoverState();
			exitButton.setIdleState();
			break;
		case 2:
			playButton.setIdleState();
			aboutButton.setIdleState();
			exitButton.setHoverState();
			break;
		default:
			break;
		}
		window.draw(logo);
		window.draw(playButton);
		window.draw(aboutButton);
		window.draw(exitButton);

		sf::Event event;
		window.pollEvent(event);
		if (event.type == sf::Event::Closed) {
			window.close();
			break;
		}
		else if (event.type == sf::Event::KeyPressed) {
			switch (event.key.code) {
			case sf::Keyboard::W:
				if (indicator > 0) {
					indicator--;
				}
				break;
			case sf::Keyboard::S:
				if (indicator < 2) {
					indicator++;
				}
				break;
			case sf::Keyboard::Enter:
				switch (indicator)
				{
				case 0:
					PLAY = true;
					break;
				case 1:
					ABOUT = true;
					break;
				case 2:
					EXIT = true;
					break;
				default:
					break;
				}
				break;
			}
		}
		window.display();
	}
	if (PLAY) {
		startGame();
	}
	else if (ABOUT) {
		about();
	}
	else if (EXIT) {
		window.close();
	}
}

void Game::about() {
	Button text(288, 288, 476, 376, &font, "Witcher themed Sokoban game.\nProject for Programowanie Obiektowe 2021-2022\nAuthors:\nFilip Marciniak\nJakub Beisert\n\nSpecial thanks to our friend Szymon Pasternak\nwho made all the beautiful graphics.\n\nPress Enter to go back to main menu.", 20, sf::Color{ 150, 120, 30 }, sf::Color{ 120, 120, 120 }, sf::Color{ 0, 230, 230 });
	window.clear(sf::Color{160, 160, 160});
	window.draw(text);
	window.display();
	bool EXIT = false;
	while (!EXIT) {
		sf::Event event;
		window.pollEvent(event);
		if (event.type == sf::Event::Closed) {
			window.close();
			break;
		}
		else if (event.type == sf::Event::KeyPressed) {
			switch (event.key.code) {
			case sf::Keyboard::Enter:
				EXIT = true;
			default:
				break;
			}
		}
	}
	Menu();
}

void Game::startGame() {
	Button text(288, 288, 476, 376, &font, "After a long and exhausting year, witchers\nmet once again during the winter in Kaer Morhen.\nUnfortunately, the witchers made quite a mess\nduring the evening feast. All the potions have been\nscattered around the witchers' lair. Help Geralt\nclean up before Vesemir realizes what happened\nlast night.\n\nUse WASD to move Geralt and R to reset the level.\nGood luck!\n\nPress Enter to continue.", 20, sf::Color{ 150, 120, 30 }, sf::Color{ 120, 120, 120 }, sf::Color{ 0, 230, 230 });
	window.clear(sf::Color{ 160, 160, 160 });
	window.draw(text);
	window.display();
	bool EXIT = false;
	while (!EXIT) {
		sf::Event event;
		window.pollEvent(event);
		if (event.type == sf::Event::Closed) {
			window.close();
			break;
		}
		else if (event.type == sf::Event::KeyPressed) {
			switch (event.key.code) {
			case sf::Keyboard::Enter:
				EXIT = true;
			default:
				break;
			}
		}
	}
	if (startLevel("levels/playground.txt")) {
		exit(0);
	}
	reset();
	if (startLevel("levels/level1.txt")) {
		exit(0);
	}
	reset();
	if (startLevel("levels/level2.txt")) {
		exit(0);
	}
	reset();
	if (startLevel("levels/level3.txt")) {
		exit(0);
	}
	reset();
	Menu();
}

int Game::startLevel(std::string levelFilePath) {
	bool RESET = false;
	bool isLevelFinished = false;
	uploadBoard(levelFilePath);
	while (isPlaying && !isLevelFinished) {
		processEvents(&RESET);
		if (isPlaying) {
			window.clear(sf::Color{ 160, 160, 160 });
			detectCollisions();
			detectFinishPoints();
			updateBoard();
			window.display();
		}
		else {
			window.close();
			return 1;
		}
		detectEndGame(&isLevelFinished);
		if (RESET == true) {
			reset();
			uploadBoard(levelFilePath);
			RESET = false;
		}
	}
	return 0;
}

void Game::reset() {
	potions.clear();
	blocks.clear();
	finishPoints.clear();
}

void Game::processEvents(bool *RESET) {

	sf::Event event;
	window.pollEvent(event);
	if (event.type == sf::Event::Closed) {
		isPlaying = false;
	}
	else if (event.type == sf::Event::KeyPressed) {
		switch (event.key.code) {
			case sf::Keyboard::A:
				player.move("left");
				break;
			case sf::Keyboard::D:
				player.move("right");
				break;
			case sf::Keyboard::W:
				player.move("up");
				break;
			case sf::Keyboard::S:
				player.move("down");
				break;
			case sf::Keyboard::R:
				*RESET = true;
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

void Game::detectEndGame(bool *isLevelFinished) {
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
		*isLevelFinished = true;
	}
}

void Game::updateBoard() {

	for (auto& block : blocks) {
		block.setPicture("pictures/block.png");
		window.draw(block);
	}

	for (auto& finishPoint : finishPoints) {
		finishPoint.setPicture();
		window.draw(finishPoint);
	}

	for (auto& potion : potions) {
		potion.setPicture();
		window.draw(potion);
	}

	window.draw(player);
}
