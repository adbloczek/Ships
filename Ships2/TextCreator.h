#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class TextCreator {
public:
	TextCreator();
	~TextCreator();
	sf::Text header(std::wstring header);
	sf::Text simpleTextOfSpecifiedSize(std::wstring text, int size);
	sf::Text WithSpecifiedSizeAndPosition(std::wstring text, int size, sf::Vector2f position);
	sf::Text insideButton(std::wstring, sf::RectangleShape button);
	sf::Text footer(std::wstring footer);

private:
	sf::Font default_font;
};

