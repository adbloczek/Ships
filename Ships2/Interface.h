#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "TextCreator.h"
#include "RectangleCreator.h"
#include <vector>
#include "ButtonWithText.h"
#include "Constants.h"
#include "WelcomeWindow.h"
#include "PositionShipsWindow.h"

class CInterface {
public:
	CInterface(sf::RenderWindow &setWindow);
	~CInterface();
	void vOpenGame();

private:
	sf::RenderWindow &window;
};

