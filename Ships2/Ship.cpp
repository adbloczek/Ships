#include "Ship.h"

Ship::Ship() {
	starting_position = sf::Vector2f(0, 0);
	is_set = false;
}

Ship::Ship(sf::Vector2f setStartingPosition, int numberOfSegments) {
	starting_position = setStartingPosition;
	CreateShip(numberOfSegments);
	orientation = VERTICAL;
	is_set = false;
}

int Ship::GetLeft() {
	return ship.getGlobalBounds().left;
}

int Ship::GetTop() {
	return ship.getGlobalBounds().top;
}

int Ship::GetWidth() {
	return ship.getGlobalBounds().width;
}

int Ship::GetHeight() {
	return ship.getGlobalBounds().height;
}

int Ship::GetOrientation() {
	return ship.getRotation();
}

sf::RectangleShape& Ship::GetShip() {
	return ship;
}

void Ship::CreateShip(int numberOfSegments) {

	for (int i = 0; i < numberOfSegments; i++) {
		ship = ship_creator.shipWithSpecifiedNumberOfSegments(numberOfSegments);
		int x = starting_position.x;
		int y = starting_position.y;
		ship.setPosition(sf::Vector2f(x, y));
		ship.setOrigin(ship.getLocalBounds().width / 2.0f, ship.getLocalBounds().height / 2.0f);
	}
}

void Ship::SetRotation(int angle) {
	ship.setRotation(abs(angle));
	if (angle == 0) orientation = HORIZONTAL;
	else if (angle == 90) orientation = VERTICAL;
}

void Ship::SetPosition(sf::Vector2i position) {
	ship.setPosition(sf::Vector2f(position.x, position.y));
}

void Ship::SetToStartingPosition() {
	ship.setPosition(starting_position);
}

void Ship::SetStatus(bool newStatus) {
	is_set = newStatus;
}

bool Ship::IsSet() {
	return is_set;
}

void Ship::RotateShip() {
	SetRotation(abs(90 - GetOrientation()));
}

void Ship::MoveShip(int mouseX, int mouseY) {
	SetPosition(sf::Vector2i(mouseX, mouseY));
}

Ship::~Ship() {

}
