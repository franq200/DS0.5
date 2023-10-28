#pragma once
#include "Menu.h"
#include "Gameplay.h"
#include <SFML/Graphics.hpp>

enum class GameState : uint8_t
{
	game = 0,
	menu
};

class Game
{
public:
	void Init();
	void Update();
private:
	void ViewInit();
	void Events();
	void LoadTextures();
	void Restart();
	void Draw();

	sf::RenderWindow m_window;
	sf::View m_view;
	GameState m_gameState = GameState::menu;
	Menu m_menu;
	Gameplay m_gameplay;
};
