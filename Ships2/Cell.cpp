#include "Cell.h"



Cell::Cell() {
	sf::RectangleShape rectangle(sf::Vector2f(0, 0));
	is_active = true;
	has_ship = false;
}

Cell::Cell(sf::RectangleShape setRectangle) {
	cell = setRectangle;
	is_active = true;
	has_ship = false;
}

sf::Color Cell::GetColor() {
	return cell.getFillColor();
}

bool Cell::isShipFitsInCell(Ship ship) {
	if (ship.GetLeft() >= cell.getGlobalBounds().left - CELL_SIZE / 2.0 && ship.GetLeft() + CELL_SIZE <= cell.getGlobalBounds().left + cell.getGlobalBounds().width + CELL_SIZE / 2.0) {
		if (ship.GetTop() >= cell.getGlobalBounds().top - CELL_SIZE / 2.0 && ship.GetTop() + CELL_SIZE <= cell.getGlobalBounds().top + cell.getGlobalBounds().width + CELL_SIZE / 2.0) {
			return true;
		}
	}
	return false;
}

void Cell::SetFillColor(sf::Color color) {
	cell.setFillColor(color);
}

void Cell::SetActiveStatus(bool newStatus) {
	is_active = newStatus;
}

void Cell::SetShipStatus(bool newStatus) {
	has_ship = newStatus;
}

bool Cell::GetActiveStatus() {
	return is_active;
}

int Cell::GetLeft() {
	return cell.getGlobalBounds().left;
}

int Cell::GetTop() {
	return cell.getGlobalBounds().top;
}

int Cell::GetWidth() {
	return cell.getGlobalBounds().width;
}

int Cell::GetHeight() {
	return cell.getGlobalBounds().height;
}

bool Cell::HasShip() {
	return has_ship;
}

void Cell::Draw(sf::RenderWindow &window) {
	window.draw(cell);
}

Cell::~Cell() {

}
