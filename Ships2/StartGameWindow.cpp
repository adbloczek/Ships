#include "StartGameWindow.h"
#include <thread>
#include <chrono>


StartGameWindow::StartGameWindow(Player *firstPlayer, Player *secondPlayer, sf::RenderWindow &setWindow) : window(setWindow) {
	first_player = firstPlayer;
	second_player = secondPlayer;
	window_title = text_creator.header(START_GAME_TITLE);
	whose_turn = FIRST;
}

void StartGameWindow::Run() {
	Draw();
	HandleActions();
}

void StartGameWindow::Draw() {
	window.clear(BACKGROUND_COLOR);
	window.draw(window_title);
	first_player->DrawMap(window);
	second_player->DrawMap(window);
}

void StartGameWindow::HandleActions() {
	if (whose_turn == SECOND) {
		if (first_player->ShootCellRandomly() == EMPTY_SHOOT) {
			window_title = text_creator.header(L"Twoj ruch");
			whose_turn = FIRST;
		}
	} else {
		sf::Event event;
		if (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				int mouse_x = sf::Mouse::getPosition(window).x;
				int mouse_y = sf::Mouse::getPosition(window).y;
				if (second_player->ShootCell(mouse_x, mouse_y) == EMPTY_SHOOT) {
					window_title = text_creator.header(L"Ruch rywala");
					whose_turn = SECOND;
				}
				Draw();
			}
		}
	}
}

StartGameWindow::~StartGameWindow() {
}
