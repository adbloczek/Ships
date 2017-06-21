#pragma once
#include <SFML/Graphics.hpp>
#include "TextCreator.h"
#include "RectangleCreator.h"
#include "ButtonWithText.h"
#include "Constants.h"
#include "Cell.h"
#include "Ship.h"
#include "Player.h"

class PositionShipsWindow {
public:
	PositionShipsWindow(Player *firstPlayer, Player *secondPlayer, sf::RenderWindow &setWindow);
	int Run();
	void Draw();
	void DrawMenuButtons();
	void CreateMenuButtons();
	int HandleActions();
	int GetClickedButton();
	~PositionShipsWindow();

private:
	sf::RenderWindow &window;
	sf::Text window_title;
	TextCreator  text_creator = TextCreator();
	RectangleCreator rectangle_creator;
	std::vector<ButtonWithText> menu_buttons;
	Player *first_player;
	Player *second_player;
	Ship *dragged_ship;
	Ship *last_ship;
};

