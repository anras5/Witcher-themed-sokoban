#include "Object.h"

Object::Object() {}

void Object::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(sprite, state);
}

void Object::setPosition(int t_X, int t_Y)
{
	sprite.setPosition(t_X, t_Y);
}

sf::Vector2i Object::getPosition()
{
	position.x = (int)sprite.getPosition().x;
	position.y = (int)sprite.getPosition().y;
	return position;
}

void Object::setPicture(const std::string filepath) {
	texture.loadFromFile(filepath);
	sprite.setTexture(texture);
}