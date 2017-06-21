#include "Player.h"
#include <stdlib.h>
#include <thread>
#include <chrono>

Player::Player(int setType, int setNumber) {
	type = setType;
	number = setNumber;
	CreateCellsMap();
	CreateShips();
}

void Player::CreateCellsMap() {
	int position_x, position_y;
	if (type == PLAYER) {
		position_x = PLAYER_X;
		position_y = PLAYER_Y;
	} else {
		position_x = COMPUTER_X;
		position_y = COMPUTER_Y;
	}
	for (int column_number = 0; column_number < NUMBER_OF_CELLS_IN_MAP; column_number++) {
		std::vector<Cell> column;
		cells_map.push_back(column);
		for (int row_number = 0; row_number < NUMBER_OF_CELLS_IN_MAP; row_number++) {
			int left = position_x - ((CELL_SIZE + 1) * NUMBER_OF_CELLS_IN_MAP / 2.0) + (column_number * (CELL_SIZE + 1));
			int top = position_y + (row_number * (CELL_SIZE + 1));
			sf::RectangleShape rectangle = RectangleCreator::cellWithSpecificPosition(sf::Vector2f(left, top));
			cells_map[column_number].push_back(Cell(rectangle));
			cells_indexes.push_back(sf::Vector2i(column_number, row_number));
		}
	}
}

void Player::CreateShips() {
	int ship_x, ship_y;
	if (type == PLAYER) {
		ship_x = PLAYER_X - 350;
		ship_y = PLAYER_Y + 50;
	}
	else {
		ship_x = COMPUTER_X;
		ship_y = COMPUTER_Y;
	}
	/*for (int i = 0; i < 4; i++) {
		if (ships.size() > 0) {
			ship_y = ships.back().GetTop() + ships.back().GetHeight() + 30 + (i * (CELL_SIZE + 1)) / 2.0;
		}
		for (int j = 0; j < 4 - i; j++) {
			ship_x = PLAYER_X - 12*CELL_SIZE + j * (CELL_SIZE + 10);
			ships.push_back(Ship(sf::Vector2f(ship_x, ship_y), i + 1));
		}

	}*/
	ships.push_back(Ship(sf::Vector2f(ship_x, ship_y), 1));
	ships.push_back(Ship(sf::Vector2f(ship_x + CELL_SIZE + 3, ship_y), 1));
	ships.push_back(Ship(sf::Vector2f(ship_x + 2*(CELL_SIZE + 3), ship_y), 1));
	ships.push_back(Ship(sf::Vector2f(ship_x + 3*(CELL_SIZE + 3), ship_y), 1));
	ships.push_back(Ship(sf::Vector2f(ship_x, ship_y + 1.5*CELL_SIZE + 2), 2));
	ships.push_back(Ship(sf::Vector2f(ship_x, ship_y + 3.5*(CELL_SIZE + 1)+2), 2));
	ships.push_back(Ship(sf::Vector2f(ship_x + 1.5 * CELL_SIZE + 4, ship_y + CELL_SIZE + 2), 2));
	ships.back().RotateShip();
	ships.push_back(Ship(sf::Vector2f(ship_x + CELL_SIZE + 3, ship_y + 3*(CELL_SIZE + 1) + 2), 3));
	ships.push_back(Ship(sf::Vector2f(ship_x + 2*CELL_SIZE + 6, ship_y + 3 * (CELL_SIZE + 1) + 2), 3));
	ships.push_back(Ship(sf::Vector2f(ship_x + 3 * CELL_SIZE + 9, ship_y + 2.5 * (CELL_SIZE + 1) + 2), 4));
}

void Player::SetTakenCellsInactive() {
	SetAllCellsActive();
	for (int i = 0; i < ships.size(); i++) {
		if (ships[i].IsSet()) {
			SetCellsInactiveAroundShip(&ships[i]);
		}
	}
}

void Player::SetAllCellsActive() {
	for (int i = 0; i < NUMBER_OF_CELLS_IN_MAP; i++) {
		for (int j = 0; j < NUMBER_OF_CELLS_IN_MAP; j++) {
			cells_map[i][j].SetFillColor(CELL_COLOR);
			cells_map[i][j].SetActiveStatus(true);
		}
	}
}

Ship* Player::GetClickedShip(int mouseX, int mouseY) {
	for (int i = 0; i < ships.size(); i++) {
		if (mouseX >= ships[i].GetLeft() && mouseX <= ships[i].GetLeft() + ships[i].GetWidth() && mouseY >= ships[i].GetTop() && mouseY <= ships[i].GetTop() + ships[i].GetHeight()) {
			return &ships[i];
			break;
		}
	}
	return NULL;
}

bool Player::TryToPutShipIntoMap(Ship *ship) {
	for (int i = 0; i < NUMBER_OF_CELLS_IN_MAP; i++) {
		for (int j = 0; j < NUMBER_OF_CELLS_IN_MAP; j++) {
			Cell cell = cells_map[i][j];
			if (cell.isShipFitsInCell(*ship)) {
				if (ship->GetWidth() / CELL_SIZE + i > NUMBER_OF_CELLS_IN_MAP || ship->GetHeight() / CELL_SIZE + j > NUMBER_OF_CELLS_IN_MAP) {
					ship->SetStatus(false);
					return false;
				}
				else {
					for (int k = i; k < i + ship->GetWidth() / CELL_SIZE; k++) {
						if (cells_map[k][j].GetActiveStatus() == false) return false;
					}
					for (int k = j; k < j + ship->GetHeight() / CELL_SIZE; k++) {
						if (cells_map[i][k].GetActiveStatus() == false) return false;
					}
					ship->SetPosition(sf::Vector2i(cell.GetLeft() + ship->GetWidth() / 2.0, cell.GetTop() +ship->GetHeight() / 2.0));
					ship->SetStatus(true);
					SetCellsInactiveAroundShip(ship);
					return true;
				}
			}
		}
	}
	return false;
}

int Player::ShootCellRandomly() {
	srand(time(NULL));
	std::this_thread::sleep_for(std::chrono::milliseconds(500 + rand() % 1500));
	if (hit_cells.size() > 0) {
		sf::Vector2i position = ChooseNextCell();
		return ShootCell(cells_map[position.x][position.y].GetLeft(), cells_map[position.x][position.y].GetTop());
	} else {
		int number = rand() % cells_indexes.size();
		sf::Vector2i indexes = cells_indexes[number];
		cells_indexes.erase(cells_indexes.begin() + number);
		cout << cells_indexes.size() << ":" <<endl;
		return ShootCell(cells_map[indexes.x][indexes.y].GetLeft(), cells_map[indexes.x][indexes.y].GetTop());
	}
}

sf::Vector2i Player::ChooseNextCell() {
	cout << "Wybieram nastepna" << endl;
	int column = hit_cells[0].x;
	int row = hit_cells[0].y;
	int last_column = hit_cells[hit_cells.size() - 1].x;
	int last_row = hit_cells[hit_cells.size() - 1].y;
	if (hit_cells.size() == 1) {
		if (column-1>=0 && cells_map[column-1][row].GetActiveStatus()) return sf::Vector2i(column-1, row);
		else if (column+1 < NUMBER_OF_CELLS_IN_MAP && cells_map[column + 1][row].GetActiveStatus()) return sf::Vector2i(column+1, row);
		else if (row - 1 >= 0 && cells_map[column][row-1].GetActiveStatus()) return sf::Vector2i(column, row-1);
		else if (row + 1 < NUMBER_OF_CELLS_IN_MAP && cells_map[column][row+1].GetActiveStatus()) return sf::Vector2i(column, row+1);
	} else {
		if (hit_cells[0].x - hit_cells[1].x != 0) {
			cout << "No elo" << endl;
			for (int i = 0; i < hit_cells.size(); i++) {
				int x = hit_cells[i].x;
				int y = hit_cells[i].y;
				if (x - 1 >= 0 && cells_map[x - 1][y].GetActiveStatus()) return sf::Vector2i(x - 1, y);
				else if (x + 1 < NUMBER_OF_CELLS_IN_MAP && cells_map[x + 1][y].GetActiveStatus()) return sf::Vector2i(x + 1, y);
			}
		} else {
			cout << "No elo2: " << row << ", " << last_row << endl;
			for (int i = 0; i < hit_cells.size(); i++) {
				int x = hit_cells[i].x;
				int y = hit_cells[i].y;
				if (y - 1 >= 0 && cells_map[x][y-1].GetActiveStatus()) return sf::Vector2i(x, y-1);
				else if (y + 1 < NUMBER_OF_CELLS_IN_MAP && cells_map[x][y+1].GetActiveStatus()) return sf::Vector2i(x, y+1);
			}
		}
	}
	return sf::Vector2i(0, 0);
}

int Player::ShootCell(int mouseX, int mouseY) {
	for (int i = 0; i < NUMBER_OF_CELLS_IN_MAP; i++) {
		for (int j = 0; j < NUMBER_OF_CELLS_IN_MAP; j++) {
			Cell cell = cells_map[i][j];
			if (mouseX >= cell.GetLeft() && mouseX <= cell.GetLeft() + CELL_SIZE && mouseY >= cell.GetTop() && mouseY <= cell.GetTop() + CELL_SIZE) {
				if (cell.GetActiveStatus() == false) {
					return INVALID_SHOOT;
				} else if (cell.HasShip()) {
					cells_map[i][j].SetActiveStatus(false);
					cells_map[i][j].SetFillColor(SHIP_COLOR);
					hit_cells.push_back(sf::Vector2i(i, j));
					if (IsShipDestroyed(i-1, j, LEFT) && IsShipDestroyed(i+1, j, RIGHT) && IsShipDestroyed(i, j-1, TOP) && IsShipDestroyed(i, j+1, DOWN)) {
						SetCellsInactiveAroundDestroyedShip(i, j);
						hit_cells.clear();
					}
					return SHIP_SHOOT;
				} else {
					cells_map[i][j].SetFillColor(INACTIVE_CELL_COLOR);
					cells_map[i][j].SetActiveStatus(false);
					DeleteCellToShot(sf::Vector2i(i, j));
					return EMPTY_SHOOT;
				}
			}
		}
	}
	return INVALID_SHOOT;
}

bool Player::IsShipDestroyedUnderCell(int column, int row) {
	return cells_map[column][row].HasShip() && cells_map[column][row].GetActiveStatus();
}

bool Player::IsShipDestroyed(int column, int row, int direction) {
	if (column < 0 || column >= NUMBER_OF_CELLS_IN_MAP || row < 0 || row >= NUMBER_OF_CELLS_IN_MAP) return true;
	if (cells_map[column][row].HasShip() && cells_map[column][row].GetActiveStatus()) return false;
	else if (cells_map[column][row].HasShip() && cells_map[column][row].GetActiveStatus() == false) {
		if (direction == LEFT) return IsShipDestroyed(column - 1, row, direction);
		else if (direction == RIGHT) return IsShipDestroyed(column + 1, row, direction);
		else if (direction == TOP) return IsShipDestroyed(column, row-1, direction);
		else if (direction == DOWN) return IsShipDestroyed(column, row+1, direction);
	}
	cout << column << ", " << row << endl;
	return true;
}

void Player::SetCellsInactiveAroundDestroyedShip(int column, int row) {
	cells_map[column][row].SetFillColor(sf::Color::Black);
	cells_map[column][row].SetActiveStatus(false);
	for (int i = column - 1; i <= column + 1; i++) {
		for (int j = row - 1; j <= row + 1; j++) {
			if (i >= 0 && i < NUMBER_OF_CELLS_IN_MAP && j >= 0 && j < NUMBER_OF_CELLS_IN_MAP) {
				if (cells_map[i][j].HasShip()) {
					if (cells_map[i][j].GetColor() != sf::Color::Black) SetCellsInactiveAroundDestroyedShip(i, j);
				} else {
					cells_map[i][j].SetFillColor(INACTIVE_CELL_COLOR);
					cells_map[i][j].SetActiveStatus(false);
					DeleteCellToShot(sf::Vector2i(i, j));
				}
			}
		}
	}
}

void Player::SetCellsInactiveAroundShip(Ship *ship) {
	for (int i = 0; i < NUMBER_OF_CELLS_IN_MAP; i++) {
		for (int j = 0; j < NUMBER_OF_CELLS_IN_MAP; j++) {
			Cell cell = cells_map[i][j];
			if (cell.GetLeft() <= ship->GetLeft() + ship->GetWidth() + CELL_SIZE && cell.GetLeft() >= ship->GetLeft() - CELL_SIZE - 1 && cell.GetTop() >= ship->GetTop() - CELL_SIZE - 1 && cell.GetTop() <= ship->GetTop() + ship->GetHeight() + CELL_SIZE) {
				cells_map[i][j].SetFillColor(INACTIVE_CELL_COLOR);
				cells_map[i][j].SetActiveStatus(false);
			}
		}
	}
}

void Player::SetCellsActiveAroundShip(Ship *ship) {
	for (int i = 0; i < NUMBER_OF_CELLS_IN_MAP; i++) {
		for (int j = 0; j < NUMBER_OF_CELLS_IN_MAP; j++) {
			Cell cell = cells_map[i][j];
			if (cell.GetLeft() <= ship->GetLeft() + ship->GetWidth() + CELL_SIZE && cell.GetLeft() >= ship->GetLeft() - CELL_SIZE - 1 && cell.GetTop() >= ship->GetTop() - CELL_SIZE - 1 && cell.GetTop() <= ship->GetTop() + ship->GetHeight() + CELL_SIZE) {
				cells_map[i][j].SetFillColor(sf::Color::Red);
				cells_map[i][j].SetActiveStatus(true);
			}
		}
	}
}

void Player::SetShipsIntoCellsMap() {
	for (int z = 0; z < ships.size(); z++) {
		for (int i = 0; i < NUMBER_OF_CELLS_IN_MAP; i++) {
			for (int j = 0; j < NUMBER_OF_CELLS_IN_MAP; j++) {
				Cell cell = cells_map[i][j];
				if (cell.GetLeft() < ships[z].GetLeft() + ships[z].GetWidth() && cell.GetLeft() >= ships[z].GetLeft() && cell.GetTop() >= ships[z].GetTop() && cell.GetTop() < ships[z].GetTop() + ships[z].GetHeight()) {
					cells_map[i][j].SetShipStatus(true);
				}
			}
		}
	}
}

void Player::PositionShipsRandomly() {
	SetAllCellsActive();
	std::vector<Cell> cells;
	for (int i = 0; i < NUMBER_OF_CELLS_IN_MAP; i++) {
		for (int j = 0; j < NUMBER_OF_CELLS_IN_MAP; j++) {
			cells.push_back(cells_map[i][j]);
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
		if (TryToPutShipIntoMap(&ships[i]) == false) {
			i--;
		}
		else {
			SetCellsInactiveAroundShip(&ships[i]);
			cells.erase(cells.begin() + cell_number);
		}
	}
}

void Player::DeleteCellToShot(sf::Vector2i index) {
	for (int i = 0; i < cells_indexes.size(); i++) {
		if (cells_indexes[i].x == index.x && cells_indexes[i].y == index.y) {
			cells_indexes.erase(cells_indexes.begin() + i);
		}
	}
}

bool Player::AreShipsPositioned() {
	return false;
}

void Player::DrawMap(sf::RenderWindow &swindow) {
	for (int i = 0; i < cells_map.size(); i++) {
		for (int j = 0; j < cells_map.size(); j++) {
			cells_map[i][j].Draw(swindow);
		}
	}
}

void Player::DrawShips(sf::RenderWindow &swindow) {
	for (int i = 0; i < ships.size(); i++) {
		swindow.draw(ships[i].GetShip());
	}
}

int Player::GetType() {
	return type;
}

int Player::getNumberOfUnpositionedShips() {
	int counter = ships.size();
	for (int i = 0; i < ships.size(); i++) {
		if (ships[i].IsSet()) counter--;
	}
	return counter;
}

Player::~Player() {

}