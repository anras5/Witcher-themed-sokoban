#pragma once
#include <SFML/Graphics.hpp>
class Object : public sf::Drawable
{
	friend class Block;
	friend class Potion;
	friend class FinishPoint;
private:
	const int TileSize = 64;
	sf::Vector2i position;
	sf::Sprite sprite;
	sf::Texture texture;
public:
	Object();
	void setPosition(int t_X, int t_Y);
	sf::Vector2i getPosition();
	void setPicture(const std::string filepath);
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
};

