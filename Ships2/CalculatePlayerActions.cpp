#include "CalculatePlayerActions.h"



CalculatePlayerActions::CalculatePlayerActions() {
}

void CalculatePlayerActions::CreateCellsMap(sf::Vector2f position, std::vector<std::vector<Cell>> &cellsMap) {
	for (int column_number = 0; column_number < NUMBER_OF_CELLS_IN_MAP; column_number++) {
		std::vector<Cell> column;
		cellsMap.push_back(column);
		for (int row_number = 0; row_number < NUMBER_OF_CELLS_IN_MAP; row_number++) {
			int left = position.x - ((CELL_SIZE + 1) * NUMBER_OF_CELLS_IN_MAP / 2.0) + (column_number * (CELL_SIZE + 1));
			int top = position.y + (row_number * (CELL_SIZE + 1));
			sf::RectangleShape rectangle = RectangleCreator::CellWithSpecificPosition(left, top);
			cellsMap[column_number].push_back(Cell(rectangle));
		}
	}
}

void CalculatePlayerActions::CreateShips(sf::Vector2f position, std::vector<Ship> &ships) {
	int ship_y = position.y;
	for (int i = 0; i < 4; i++) {
		if (ships.size() > 0) {
			ship_y = ships.back().GetTop() + ships.back().GetHeight() + 30 + (i * (CELL_SIZE + 1)) / 2.0;
		}
		for (int j = 0; j < 4 - i; j++) {
			int ship_x = position.x - 400 + j * (CELL_SIZE + 10);
			ships.push_back(Ship(sf::Vector2f(ship_x, ship_y), i + 1));
		}

	}
}

void CalculatePlayerActions::SetTakenCellsInactive(std::vector<Ship> &ships, std::vector<std::vector<Cell>> &cellsMap) {
	SetAllCellsActive(cellsMap);
	for (int i = 0; i < ships.size(); i++) {
		if (ships[i].IsSet()) SetCellsInactiveAroundShip(&ships[i], cellsMap);
	}
}

void CalculatePlayerActions::SetAllCellsActive(std::vector<std::vector<Cell>> &cellsMap) {
	for (int i = 0; i < NUMBER_OF_CELLS_IN_MAP; i++) {
		for (int j = 0; j < NUMBER_OF_CELLS_IN_MAP; j++) {
			Cell cell = cellsMap[i][j];
			cell.SetFillColor(sf::Color::Red);
			cell.SetActiveStatus(true);
		}
	}
}

Ship* CalculatePlayerActions::GetClickedShip(std::vector<Ship> &ships, sf::RenderWindow &window) {
	cout << endl;
	int mouse_x = sf::Mouse::getPosition(window).x;
	int mouse_y = sf::Mouse::getPosition(window).y;
	for (int i = 0; i < ships.size(); i++) {
		if (mouse_x >= ships[i].GetLeft() && mouse_x <= ships[i].GetLeft() + ships[i].GetWidth() && mouse_y >= ships[i].GetTop() && mouse_y <= ships[i].GetTop() + ships[i].GetHeight()) {
			return &ships[i];
			break;
		}
	}
	return NULL;
}

void CalculatePlayerActions::RotateShip(Ship *ship) {
	if (ship != NULL) {
		ship->SetRotation(abs(90 - ship->GetOrientation()));

	}
}

void CalculatePlayerActions::MoveShip(Ship *ship, sf::RenderWindow &window) {
	ship->SetPosition(sf::Mouse::getPosition(window));
}

bool CalculatePlayerActions::TryToPutShipIntoMap(Ship *ship, std::vector<std::vector<Cell>> &cellsMap) {
	for (int i = 0; i < NUMBER_OF_CELLS_IN_MAP; i++) {
		for (int j = 0; j < NUMBER_OF_CELLS_IN_MAP; j++) {
			Cell cell = cellsMap[i][j];
			if (cell.isShipFitsInCell(*ship)) {
				if (ship->GetWidth() / CELL_SIZE + i > NUMBER_OF_CELLS_IN_MAP || ship->GetHeight() / CELL_SIZE + j > NUMBER_OF_CELLS_IN_MAP) {
					ship->SetStatus(false);
					return false;
				}
				else {
					for (int k = i; k < i + ship->GetWidth() / CELL_SIZE; k++) {
						if (cellsMap[k][j].GetActiveStatus() == false) return false;
					}
					for (int k = j; k < j + ship->GetHeight() / CELL_SIZE; k++) {
						if (cellsMap[i][k].GetActiveStatus() == false) return false;
					}
					ship->SetPosition(sf::Vector2i(cell.GetLeft() + ship->GetWidth() / 2.0, cell.GetTop() + ship->GetHeight() / 2.0));
					ship->SetStatus(true);
					return true;
				}
			}
		}
	}
	return false;
}

void CalculatePlayerActions::SetCellsInactiveAroundShip(Ship *ship, std::vector<std::vector<Cell>> &cellsMap) {
	for (int i = 0; i < NUMBER_OF_CELLS_IN_MAP; i++) {
		for (int j = 0; j < NUMBER_OF_CELLS_IN_MAP; j++) {
			Cell cell = cellsMap[i][j];
			if (cell.GetLeft() <= ship->GetLeft() + ship->GetWidth() + CELL_SIZE && cell.GetLeft() >= ship->GetLeft() - CELL_SIZE - 1 && cell.GetTop() >= ship->GetTop() - CELL_SIZE - 1 && cell.GetTop() <= ship->GetTop() + ship->GetHeight() + CELL_SIZE) {
				cell.SetFillColor(sf::Color::Black);
				cell.SetActiveStatus(false);
			}
		}
	}
}

void CalculatePlayerActions::PositionShipsRandomly(std::vector<Ship> &ships, std::vector<std::vector<Cell>> &cellsMap) {
	SetAllCellsActive(cellsMap);
	std::vector<Cell> cells;
	for (int i = 0; i < NUMBER_OF_CELLS_IN_MAP; i++) {
		for (int j = 0; j < NUMBER_OF_CELLS_IN_MAP; j++) {
			cells.push_back(cellsMap[i][j]);
		}
	}
	srand(time(NULL));

	for (int i = 0; i < ships.size(); i++) {
		int cell_number = rand() % cells.size();
		if (rand() % 2 == 0) {
			ships[i].SetRotation(90);
		}
		else {
			ships[i].SetRotation(0);
		}
		ships[i].SetPosition(sf::Vector2i(cells[cell_number].GetLeft() + 5, cells[cell_number].GetTop() + 5));
		if (TryToPutShipIntoMap(&ships[i], cellsMap) == false) {
			i--;
		}
		else {
			SetCellsInactiveAroundShip(&ships[i], cellsMap);
			cells.erase(cells.begin() + cell_number);
		}
	}
}

bool CalculatePlayerActions::AreShipsPositioned(std::vector<Ship> &ships) {
	return false;
}

CalculatePlayerActions::~CalculatePlayerActions() {
}
