#pragma once
#include <SFML/Graphics.hpp>
#include "Ship.h"
class Cell {
	friend class SetFirstPlayerShipsWindow;
	friend class PositionShipsWindow;
public:
	Cell();
	Cell(sf::RectangleShape setRectangle);
	bool isShipFitsInCell(Ship rectangle);
	bool HasShip();
	void SetShipStatus(bool newStatus);
	void SetFillColor(sf::Color color);
	void SetActiveStatus(bool newStatus);
	bool GetActiveStatus();
	int GetLeft();
	int GetTop();
	int GetWidth();
	int GetHeight();
	sf::Color GetColor();
	void Draw(sf::RenderWindow &window);
	sf::RectangleShape* GetCell();

	~Cell();
private:
	sf::RectangleShape cell;
	bool is_active;
	bool has_ship;
};

