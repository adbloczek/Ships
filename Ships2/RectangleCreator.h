#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class RectangleCreator {
public:
	RectangleCreator();
	static sf::RectangleShape selectionButtonUnderText(sf::Text text);
	static sf::RectangleShape selectionButtonUnderAnotherButton(sf::RectangleShape anotherButton);
	static sf::RectangleShape selectionButtonWithSpecificPosition(sf::Vector2f position);
	static sf::RectangleShape cellWithSpecificPosition(sf::Vector2f position);
	static sf::RectangleShape shipWithSpecifiedNumberOfSegments(int numberOfSegments);
	~RectangleCreator();
};

