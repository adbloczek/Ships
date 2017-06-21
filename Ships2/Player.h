#pragma once
#include <SFML/Graphics.hpp>
#include "TextCreator.h"
#include "RectangleCreator.h"
#include "ButtonWithText.h"
#include "Constants.h"
#include "Cell.h"
#include "Ship.h"
#include "CalculatePlayerActions.h"
#include <stdlib.h>
#include <Windows.h>
class Player {
public:
	Player(int setType, int setNumber);
	Ship* GetClickedShip(int mouseX, int mouseY);
	bool TryToPutShipIntoMap(Ship *ship);
	void SetTakenCellsInactive();
	void SetCellsInactiveAroundShip(Ship *ship);
	void SetCellsActiveAroundShip(Ship *ship);
	void SetShipsIntoCellsMap();
	int ShootCell(int mouseX, int mouseY);
	int ShootCellRandomly();
	sf::Vector2i ChooseNextCell();
	bool IsShipDestroyed(int column, int row, int direction);
	bool IsShipDestroyedUnderCell(int column, int row);
	void SetCellsInactiveAroundDestroyedShip(int column, int row);
	void SetAllCellsActive();
	void PositionShipsRandomly();
	bool AreShipsPositioned();
	void DrawMap(sf::RenderWindow &swindow);
	void DrawShips(sf::RenderWindow &swindow);
	void DeleteCellToShot(sf::Vector2i index);
	int getNumberOfUnpositionedShips();
	int GetType();
	~Player();

private:
	int type;
	int number;
	std::vector<std::vector<Cell>> cells_map;
	std::vector<Ship> ships;
	Ship *dragged_ship;
	void CreateCellsMap();
	void CreateShips();
	std::vector<sf::Vector2i> hit_cells;
	std::vector<sf::Vector2i> cells_indexes;
};

