#include "ButtonWithText.h"
#include <SFML/Graphics.hpp>



ButtonWithText::ButtonWithText() {
}

ButtonWithText::ButtonWithText(sf::RectangleShape setButton, sf::Text setText) {
	button = setButton;
	text = setText;
}

sf::RectangleShape ButtonWithText::getButton() {
	return button;
}

sf::Text ButtonWithText::getButtonText() {
	return text;
}

bool ButtonWithText::isButtonClicked(sf::Vector2i mousePosition) {
	int button_width = button.getGlobalBounds().width;
	int button_left = button.getGlobalBounds().left;
	int button_height = button.getGlobalBounds().height;
	int button_top = button.getGlobalBounds().top;
	if (mousePosition.x >= button_left && mousePosition.x <= button_left + button_width && mousePosition.y >= button_top && mousePosition.y <= button_top + button_height)
		return true;

	return false;
}

ButtonWithText::~ButtonWithText() {
}
