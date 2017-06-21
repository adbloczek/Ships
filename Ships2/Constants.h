#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

const int LEFT = 0;
const int RIGHT = 1;
const int TOP = 2;
const int DOWN = 3;
const int SHIP_SHOOT = 0;
const int EMPTY_SHOOT = 1;
const int INVALID_SHOOT = 2;

const int WELCOME_MENU_ANSWER = -1;
const int PLAYER_VS_COMPUTER_ANSWER = 0;
const int START_GAME_ANSWER = 11;
const int STATISTICS_ANSWER = 1;
const int SETTINGS_ANSWER = 2;
const int EXIT_ANSWER = 3;

const string DEFAULT_FONT = "arial.ttf";
const wstring GAME_NAME = L"Gra w statki";
const wstring MAIN_WINDOW_WELCOME = L"Witaj w grze Statki!";
const int HEADER_FONT_SIZE = 70;
const int FOOTER_FONT_SIZE = 10;

const sf::Vector2f DEFAULT_BUTTON_SIZE = sf::Vector2f(200, 60);
const wstring PLAYER_VS_COMPUTER = L"Gracz vs komputer";
const wstring STATISTICS = L"Statystyki";
const wstring SETTINGS = L"Ustawienia";
const wstring EXIT = L"Wyjdz";
const int DEFAULT_BUTTON_FONT_SIZE = 20;

const wstring SET_PLAYER_SHIPS = L"Ustaw swoje statki na odpowiednich pozycjach";
const wstring START_GAME_TITLE = L"Zniszcz statki przeciwnika";
const wstring START_GAME = L"Rozpocznij gre";
const wstring POSITION_SHIPS_AUTOMATICALLY = L"Rozstaw losowo";
const int NUMBER_OF_CELLS_IN_MAP = 10;
const int CELL_SIZE = 30;

const int I_DEFAULT_WIDTH = 1366;
const int I_DEFAULT_HEIGTH = 680;

const int VERTICAL = 0;
const int HORIZONTAL = 1;

const bool DONE = true;
const bool UNDONE = false;

const int FIRST = 0;
const int SECOND = 1;
const int PLAYER = 0;
const int COMPUTER = 1;
const int PLAYER_X = 450;
const int PLAYER_Y = 250;
const int COMPUTER_X = I_DEFAULT_WIDTH - 450;
const int COMPUTER_Y = 250;

//Positions
const sf::Vector2i LAST_SHIP_POSITION = sf::Vector2i(150.0f, 550.0f);

//Texts
const wstring FOOTER_TEXT = L"Gra wykonana przez Micha³a Ga³eckiego.\nProgram zaliczeniowy na ZMPO, 2016 r";
const int FOOTER_DISTANCE_FROM_FRAME = 5;
const int HEADER_DISTANCE_FROM_FRAME = 10;
const float BUTTON_OUTLINE_THICKNESS = 1.0f;
const float SHIP_OUTLINE_THICKNESS = 1.0f;
const float CELL_OUTLINE_THICKNESS = 1.0f;

//Colors
const sf::Color BACKGROUND_COLOR = sf::Color(115, 180, 255);
const sf::Color HEADER_TEXT_COLOR = sf::Color(0, 100, 210);
const sf::Color FOOTER_TEXT_COLOR = sf::Color(0, 100, 210);
const sf::Color BUTTON_COLOR = sf::Color(20, 110, 215);
const sf::Color BUTTON_TEXT_COLOR = sf::Color(47, 47, 130);
const sf::Color BUTTON_OUTLINE_COLOR = sf::Color(15, 100, 200);
const sf::Color CELL_COLOR = sf::Color(70, 135, 210);
const sf::Color CELL_OUTLINE_COLOR = sf::Color(0, 0, 0);
const sf::Color INACTIVE_CELL_COLOR = sf::Color(80, 145, 210);
const sf::Color SHIP_COLOR = sf::Color(15, 80, 150);
const sf::Color SHIP_OUTLINE_COLOR = sf::Color(10, 90, 150);