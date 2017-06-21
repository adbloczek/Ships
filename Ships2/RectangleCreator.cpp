#include "RectangleCreator.h"
#include "Constants.h"


RectangleCreator::RectangleCreator() {
}

sf::RectangleShape RectangleCreator::selectionButtonUnderText(sf::Text text) {
	sf::RectangleShape button(DEFAULT_BUTTON_SIZE);
	button.setFillColor(BUTTON_COLOR);
	button.setPosition(I_DEFAULT_WIDTH / 2.0f, text.getLocalBounds().top + text.getLocalBounds().height + 150);
	button.setOrigin(button.getLocalBounds().width / 2.0f, button.getLocalBounds().height / 2.0f);
	button.setOutlineColor(BUTTON_OUTLINE_COLOR);
	button.setOutlineThickness(BUTTON_OUTLINE_THICKNESS);
	return button;
}

sf::RectangleShape RectangleCreator::selectionButtonUnderAnotherButton(sf::RectangleShape anotherButton) {
	sf::RectangleShape button(DEFAULT_BUTTON_SIZE);
	button.setFillColor(BUTTON_COLOR);
	button.setPosition(I_DEFAULT_WIDTH / 2.0f, anotherButton.getGlobalBounds().top + anotherButton.getGlobalBounds().height + 50);
	button.setOrigin(button.getLocalBounds().width / 2.0f, button.getLocalBounds().height / 2.0f);
	button.setOutlineColor(BUTTON_OUTLINE_COLOR);
	button.setOutlineThickness(BUTTON_OUTLINE_THICKNESS);
	return button;
}

sf::RectangleShape RectangleCreator::selectionButtonWithSpecificPosition(sf::Vector2f position) {
	sf::RectangleShape rectangle(DEFAULT_BUTTON_SIZE);
	rectangle.setFillColor(BUTTON_COLOR);
	rectangle.setPosition(position);
	rectangle.setOrigin(rectangle.getLocalBounds().width / 2.0f, rectangle.getLocalBounds().height / 2.0f);
	rectangle.setOutlineColor(BUTTON_OUTLINE_COLOR);
	rectangle.setOutlineThickness(BUTTON_OUTLINE_THICKNESS);
	return rectangle;
}

sf::RectangleShape RectangleCreator::cellWithSpecificPosition(sf::Vector2f position) {
	sf::RectangleShape rectangle(sf::Vector2f(CELL_SIZE, CELL_SIZE));
	rectangle.setFillColor(CELL_COLOR);
	//rectangle.setOutlineColor(CELL_OUTLINE_COLOR);
	//rectangle.setOutlineThickness(CELL_OUTLINE_THICKNESS);
	rectangle.setPosition(position);
	rectangle.setOrigin(rectangle.getLocalBounds().width / 2.0f, rectangle.getLocalBounds().height / 2.0f);
	return rectangle;
}

sf::RectangleShape RectangleCreator::shipWithSpecifiedNumberOfSegments(int numberOfSegments) {
	sf::RectangleShape segment(sf::Vector2f(CELL_SIZE, (CELL_SIZE)*numberOfSegments + numberOfSegments-1));
	segment.setFillColor(SHIP_COLOR);
	//segment.setOutlineColor(SHIP_OUTLINE_COLOR);
	//segment.setOutlineThickness(SHIP_OUTLINE_THICKNESS);
	segment.setOrigin(segment.getLocalBounds().width / 2.0f, segment.getLocalBounds().height / 2.0f);
	return segment;
}

RectangleCreator::~RectangleCreator() {
}
