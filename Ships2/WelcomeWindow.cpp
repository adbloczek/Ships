#include "WelcomeWindow.h"

WelcomeWindow::WelcomeWindow(sf::RenderWindow &setWindow) : window(setWindow) {
	title = text_creator.header(MAIN_WINDOW_WELCOME);
	footer = text_creator.footer(FOOTER_TEXT);
	createMenuButtons();
}

int WelcomeWindow::run() {
	draw();
	return handleActions();
}

void WelcomeWindow::createMenuButtons() {
	sf::RectangleShape button = rectangle_creator.selectionButtonUnderText(title);
	sf::Text text = text_creator.insideButton(PLAYER_VS_COMPUTER, button);
	menu_buttons.push_back(ButtonWithText(button, text));

	button = rectangle_creator.selectionButtonUnderAnotherButton(button);
	text = text_creator.insideButton(STATISTICS, button);
	menu_buttons.push_back(ButtonWithText(button, text));

	button = rectangle_creator.selectionButtonUnderAnotherButton(button);
	text = text_creator.insideButton(SETTINGS, button);
	menu_buttons.push_back(ButtonWithText(button, text));

	button = rectangle_creator.selectionButtonUnderAnotherButton(button);
	text = text_creator.insideButton(EXIT, button);
	menu_buttons.push_back(ButtonWithText(button, text));
}

void WelcomeWindow::draw() {
	window.clear(BACKGROUND_COLOR);
	window.draw(title);
	window.draw(footer);
	drawButtons();
}

void WelcomeWindow::drawButtons() {
	for (int i = 0; i < menu_buttons.size(); i++) {
		window.draw(menu_buttons[i].getButton());
		window.draw(menu_buttons[i].getButtonText());
	}
}

int WelcomeWindow::handleActions() {
	sf::Event event;
	if (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) window.close();
		else if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			return getClickedButton();
		}
	}
	return WELCOME_MENU_ANSWER;
}

int WelcomeWindow::getClickedButton() {
	for (int i = 0; i < menu_buttons.size(); i++) {
		if (menu_buttons[i].isButtonClicked(sf::Mouse::getPosition(window))) return i;
	}
	return WELCOME_MENU_ANSWER;
}

WelcomeWindow::~WelcomeWindow() {
}
