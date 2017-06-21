#include "TextCreator.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Constants.h"

TextCreator::TextCreator() {
	default_font.loadFromFile(DEFAULT_FONT);
}

sf::Text TextCreator::simpleTextOfSpecifiedSize(std::wstring text, int size) {
	sf::Text simple_text(text, default_font, size);
	return simple_text;
}

sf::Text TextCreator::WithSpecifiedSizeAndPosition(std::wstring text, int size, sf::Vector2f position) {
	sf::Text simple_text(text, default_font, size);
	simple_text.setFillColor(FOOTER_TEXT_COLOR);
	simple_text.setPosition(position);
	return simple_text;
}

sf::Text TextCreator::header(std::wstring header) {
	sf::Text text = simpleTextOfSpecifiedSize(header, HEADER_FONT_SIZE);
	int corrected_size = HEADER_FONT_SIZE - 1;
	while (text.getGlobalBounds().width >= I_DEFAULT_WIDTH - 2*HEADER_DISTANCE_FROM_FRAME) {
		text.setCharacterSize(corrected_size--);
	}
	text.setFillColor(HEADER_TEXT_COLOR);
	text.setPosition(I_DEFAULT_WIDTH / 2.0f, 100);
	text.setOrigin(text.getLocalBounds().width / 2.0f, text.getLocalBounds().height / 2.0f);
	return text;
}

sf::Text TextCreator::insideButton(std::wstring text, sf::RectangleShape button) {
	sf::Text button_text = simpleTextOfSpecifiedSize(text, DEFAULT_BUTTON_FONT_SIZE);
	button_text.setFillColor(BUTTON_TEXT_COLOR);
	button_text.setPosition(button.getGlobalBounds().left + button.getGlobalBounds().width / 2.0, button.getGlobalBounds().top + button.getGlobalBounds().height / 2);
	button_text.setOrigin(button_text.getGlobalBounds().width / 2.0f, button_text.getGlobalBounds().height / 2.0f);
	return button_text;
}

sf::Text TextCreator::footer(std::wstring footer) {
	sf::Text text = simpleTextOfSpecifiedSize(footer, FOOTER_FONT_SIZE);
	text.setFillColor(FOOTER_TEXT_COLOR);
	text.setPosition(FOOTER_DISTANCE_FROM_FRAME, I_DEFAULT_HEIGTH - FOOTER_DISTANCE_FROM_FRAME - text.getGlobalBounds().height);
	return text;
}

TextCreator::~TextCreator() {
}
