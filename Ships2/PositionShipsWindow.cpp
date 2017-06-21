#include "PositionShipsWindow.h"



PositionShipsWindow::PositionShipsWindow(Player *firstPlayer, Player *secondPlayer, sf::RenderWindow &setWindow) : window(setWindow) {
	first_player = firstPlayer;
	second_player = secondPlayer;
	if (second_player->GetType() == COMPUTER) second_player->PositionShipsRandomly();
	window_title = text_creator.header(SET_PLAYER_SHIPS);
	CreateMenuButtons();
}

void PositionShipsWindow::CreateMenuButtons() {
	sf::RectangleShape button = rectangle_creator.selectionButtonWithSpecificPosition(sf::Vector2f(I_DEFAULT_WIDTH/2.0,200));
	sf::Text text = text_creator.insideButton(START_GAME, button);
	menu_buttons.push_back(ButtonWithText(button, text));

	button = rectangle_creator.selectionButtonWithSpecificPosition(sf::Vector2f(PLAYER_X, PLAYER_Y+11*CELL_SIZE));
	text = text_creator.insideButton(POSITION_SHIPS_AUTOMATICALLY, button);
	menu_buttons.push_back(ButtonWithText(button, text));
}

int PositionShipsWindow::Run() {
	Draw();
	int answer = HandleActions();
	return answer;
}

void PositionShipsWindow::Draw() {
	window.clear(BACKGROUND_COLOR);
	window.draw(window_title);
	window.draw(text_creator.WithSpecifiedSizeAndPosition(L"Pozosta³o " + std::to_wstring(first_player->getNumberOfUnpositionedShips()) + L" statków \ndo rozstawienia", 17, sf::Vector2f(85,PLAYER_Y-15)));
	DrawMenuButtons();
	first_player->DrawMap(window);
	first_player->DrawShips(window);
}

void PositionShipsWindow::DrawMenuButtons() {
	for (int i = 0; i < menu_buttons.size(); i++) {
		window.draw(menu_buttons[i].getButton());
		window.draw(menu_buttons[i].getButtonText());
	}
}

int PositionShipsWindow::HandleActions() {
	cout << "Test" << endl;
	sf::Event event;
	if (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) window.close();
		if (dragged_ship == NULL) {
			if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				dragged_ship = first_player->GetClickedShip(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
				if (dragged_ship != NULL)
					if (dragged_ship->IsSet()) {
						dragged_ship->SetStatus(false);
						first_player->SetCellsActiveAroundShip(dragged_ship);
						first_player->SetTakenCellsInactive();
					}
				int answer = GetClickedButton();
				if (answer == 1) {
					first_player->SetAllCellsActive();
					first_player->SetShipsIntoCellsMap();
					second_player->SetAllCellsActive();
					second_player->SetShipsIntoCellsMap();
					return START_GAME_ANSWER;
				}
				else if (answer == 2) first_player->PositionShipsRandomly();
			} else if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				Ship *clicked_ship = first_player->GetClickedShip(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
				clicked_ship->RotateShip();
				dragged_ship = clicked_ship;
				if (dragged_ship->IsSet()) {
					dragged_ship->SetStatus(false);
					first_player->SetCellsActiveAroundShip(dragged_ship);
					first_player->SetTakenCellsInactive();
				}
			}
		} else {
			if (event.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				dragged_ship->SetStatus(false);
				dragged_ship->SetPosition(sf::Mouse::getPosition(window));
			}
			else {
				if (first_player->TryToPutShipIntoMap(dragged_ship) == false) {
					if (last_ship == NULL) {
						dragged_ship->SetPosition(LAST_SHIP_POSITION);
						last_ship = dragged_ship;
					} else if (last_ship == dragged_ship) {
						dragged_ship->SetPosition(LAST_SHIP_POSITION);
					} else {
						if (last_ship->GetOrientation() == 90)
							last_ship->RotateShip();
						last_ship->SetToStartingPosition();
						dragged_ship->SetPosition(LAST_SHIP_POSITION);
						last_ship = dragged_ship;
					}
				}
				dragged_ship = NULL;
			}
		}
	}
	return PLAYER_VS_COMPUTER_ANSWER;
}

int PositionShipsWindow::GetClickedButton() {
	for (int i = 0; i < menu_buttons.size(); i++) {
		if (menu_buttons[i].isButtonClicked(sf::Mouse::getPosition(window))) return i+1;
	}
	return PLAYER_VS_COMPUTER_ANSWER;
}

PositionShipsWindow::~PositionShipsWindow() {
}
