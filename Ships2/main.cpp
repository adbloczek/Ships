//#include "vld.h"
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "WelcomeWindow.h"
#include "PositionShipsWindow.h"
#include "StartGameWindow.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(I_DEFAULT_WIDTH, I_DEFAULT_HEIGTH, 32), GAME_NAME, sf::Style::Close);
	window.setFramerateLimit(60);
	WelcomeWindow welcome_window(window);
	Player first_player(PLAYER, FIRST);
	Player second_player(COMPUTER, SECOND);
	PositionShipsWindow position_ships_window(&first_player, &second_player, window);
	StartGameWindow start_game_window(&first_player, &second_player, window);
	int iUserAnswer = WELCOME_MENU_ANSWER;
	while (window.isOpen()) {
		switch (iUserAnswer) {
		case PLAYER_VS_COMPUTER_ANSWER: {
			iUserAnswer = position_ships_window.Run();
			break;
		} case START_GAME_ANSWER: {
			start_game_window.Run();
			iUserAnswer = START_GAME_ANSWER;
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
			iUserAnswer = welcome_window.run();
		}
		}
		window.display();
	}
	return 0;
}