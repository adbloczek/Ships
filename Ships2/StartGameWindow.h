#pragma once
#include <SFML/Graphics.hpp>
#include "TextCreator.h"
#include "RectangleCreator.h"
#include "ButtonWithText.h"
#include "Constants.h"
#include "Cell.h"
#include "Ship.h"
#include "Player.h"

class StartGameWindow {
public:
	void Run();
	void Draw();
	void HandleActions();
	StartGameWindow(Player *firstPlayer, Player *secondPlayer, sf::RenderWindow &setWindow);
	~StartGameWindow();

private:
	TextCreator  text_creator = TextCreator();
	sf::RenderWindow &window;
	sf::Text window_title;
	Player *first_player;
	Player *second_player;
	int whose_turn;
};

