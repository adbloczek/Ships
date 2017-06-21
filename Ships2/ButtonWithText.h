#pragma once
#include <SFML/Graphics.hpp>
class ButtonWithText {
public:
	ButtonWithText();
	ButtonWithText(sf::RectangleShape setButton, sf::Text setText);
	sf::RectangleShape getButton();
	sf::Text getButtonText();
	bool isButtonClicked(sf::Vector2i mousePosition);
	~ButtonWithText();

private:
	sf::RectangleShape button;
	sf::Text text;
};

