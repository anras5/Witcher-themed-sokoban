#pragma once
#include <SFML/Graphics.hpp>


class Player : public sf::Drawable
{
private:
	const int TileSize = 64;
	sf::Sprite sprite;
	sf::Texture texture;
	std::string currentDirection;
	sf::Vector2i position;

public:
	Player();
	~Player() = default;
	void move(const std::string& direction);
	void undoMove();
	void setPosition(int t_X, int t_Y);
	sf::Vector2i getPosition();
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
	std::string getCurrentDirection() {
		return currentDirection;
	}

};

