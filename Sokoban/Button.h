#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

enum button_states {
	BTN_IDLE = 0,
	BTN_HOVER,
};

class Button : public sf::Drawable
{
public:
	Button() = delete;
	Button(float t_X, float t_Y, float width, float height,
		sf::Font* font, std::string text, int textSize,
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	~Button() = default;

	void setHoverState();
	void setIdleState();
	void draw(sf::RenderTarget& target, sf::RenderStates state)const override;


private:
	short unsigned buttonState;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

};

