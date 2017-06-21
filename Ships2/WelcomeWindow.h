#pragma once
#include <SFML/Graphics.hpp>
#include "TextCreator.h"
#include "RectangleCreator.h"
#include "ButtonWithText.h"
#include "Constants.h"

class WelcomeWindow {
public:
	WelcomeWindow(sf::RenderWindow &setWindow);
	int run();
	~WelcomeWindow();

private:
	sf::RenderWindow &window;
	sf::Text title;
	sf::Text footer;
	TextCreator  text_creator = TextCreator();
	RectangleCreator rectangle_creator;
	std::vector<ButtonWithText> menu_buttons;;

	void draw();
	void drawButtons();
	int handleActions();
	void createMenuButtons();
	int getClickedButton();
};

