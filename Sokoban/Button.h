#pragma once
#include <SFML/Graphics.hpp>

enum button_states {
	BTN_IDLE = 0,
	BTN_HOVER,
	BTN_PRESSED
};

class Button
{
public:
	Button(float t_X, float t_Y, float width, float height,
		sf::Font* font, std::string text,
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);

	const bool isPressed() const;

	void update(sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);


private:
	short unsigned buttonState;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

};

