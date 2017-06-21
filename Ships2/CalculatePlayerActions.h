#pragma once
#include "Ship.h"
#include "Constants.h"
#include "Cell.h"

class CalculatePlayerActions {
public:
	CalculatePlayerActions();
	static void CreateCellsMap(sf::Vector2f position, std::vector<std::vector<Cell>> &cellsMap);
	static void CreateShips(sf::Vector2f position, std::vector<Ship>& ships);
	static Ship* GetClickedShip(std::vector<Ship>& ships, sf::RenderWindow &window);
	static void RotateShip(Ship *ship);
	static void MoveShip(Ship *ship, sf::RenderWindow &window);
	static bool TryToPutShipIntoMap(Ship *ship, std::vector<std::vector<Cell>> &cellsMap);
	static void SetTakenCellsInactive(std::vector<Ship> &ships, std::vector<std::vector<Cell>> &cellsMap);
	static void SetCellsInactiveAroundShip(Ship *ship, std::vector<std::vector<Cell>> &cellsMap);
	static void SetAllCellsActive(std::vector<std::vector<Cell>> &cellsMap);
	static void PositionShipsRandomly(std::vector<Ship> &ships, std::vector<std::vector<Cell>> &cellsMap);
	static bool AreShipsPositioned(std::vector<Ship> &ships);
	~CalculatePlayerActions();
};

