#include "Interface.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Constants.h"
#include "TextCreator.h"
#include "Player.h"
#include "PositionShipsWindow.h"

CInterface::CInterface(sf::RenderWindow &setWindow) : window(setWindow) {

}

void CInterface::vOpenGame() {
	WelcomeWindow welcome_window(window);
	Player *first_player = new Player(sf::Vector2f(530, 250), window);
	Player *second_player = new Player(sf::Vector2f(50, 50), window);
	PositionShipsWindow *position_ships_window = new PositionShipsWindow(first_player, second_player, window);
	int iUserAnswer = WELCOME_MENU_ANSWER;
	while (window.isOpen()) {
		switch (iUserAnswer) {
		case PLAYER_VS_COMPUTER_ANSWER: {
			position_ships_window->Run();
			iUserAnswer = position_ships_window->GetClickedButton();
			break;
		} case STATISTICS_ANSWER: {
			cout << "1" << endl;
			break;
		} case SETTINGS_ANSWER: {
			cout << "2" << endl;
			break;
		} case EXIT_ANSWER: {
			window.close();
			break;
		}
		default: {
			welcome_window.Run();
			iUserAnswer = welcome_window.GetClickedButton();
		}
		}
		window.display();
	}
	delete first_player;
	delete second_player;
	delete position_ships_window;
}


CInterface::~CInterface() {
}
