#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "RectangleCreator.h"
#include "Constants.h"

class Ship {
public:
	Ship();
	Ship(sf::Vector2f setStartingPosition, int numberOfSegments);
	void SetRotation(int angle);
	void SetPosition(sf::Vector2i position);
	void SetToStartingPosition();
	void SetStatus(bool newStatus);
	bool IsSet();
	int GetLeft();
	int GetTop();
	int GetWidth();
	int GetHeight();
	int GetOrientation();
	void RotateShip();
	void MoveShip(int mouseX, int mouseY);
	sf::RectangleShape& GetShip();
	~Ship();

private:
	sf::RectangleShape ship;
	sf::Vector2f starting_position;
	RectangleCreator ship_creator;
	bool is_set;
	int orientation;
	void CreateShip(int numberOfSegments);
};

