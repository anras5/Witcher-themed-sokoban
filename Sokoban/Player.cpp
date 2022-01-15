#include "Player.h"

Player::Player()
{
	texture.loadFromFile("pictures/geraltRight.png");
	sprite.setTexture(texture);
	currentDirection = "right";
}

void Player::setPosition(int t_X, int t_Y) {
	sprite.setPosition(t_X, t_Y);
}

sf::Vector2i Player::getPosition()
{
	position.x = (int)sprite.getPosition().x;
	position.y = (int)sprite.getPosition().y;
	return position;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(sprite);
}

void Player::move(const std::string& direction)
{
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

void Player::undoMove() {
	// TODO: dorobic obracanie sie Geralta

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


