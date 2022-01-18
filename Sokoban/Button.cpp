#include "Button.h"
#include "Button.h"

Button::Button(float t_X, float t_Y, float width, float height,
	sf::Font* font, std::string text, int textSize,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	this->buttonState = BTN_IDLE;

	this->shape.setPosition(sf::Vector2f(t_X, t_Y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setOrigin(sf::Vector2f(width / 2.f, height / 2.f));

	this->idleColor = idleColor;
	this->shape.setFillColor(this->idleColor);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::Black);
	this->text.setCharacterSize(textSize);
	this->text.setPosition(
		this->shape.getPosition().x - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y - this->text.getGlobalBounds().height / 2.f
	);
}

void Button::setHoverState(){
	this->buttonState = BTN_HOVER;
	this->text.setFillColor(sf::Color::Yellow);
}

void Button::setIdleState(){
	this->buttonState = BTN_IDLE;
	this->text.setFillColor(sf::Color::Black);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates state) const{
	target.draw(this->shape, state);
	target.draw(this->text, state);
}