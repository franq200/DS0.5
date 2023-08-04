#pragma once
#include "Map.h"
#include "Character.h"
#include <SFML/Graphics.hpp>

class Game
{
public:
	void Init();
	void Update();
private:
	void Draw();
	void Events();
	void LoadTextures();
	void TryMoveCharacter();
	void MoveCharacter(sf::Vector2f moveValue);
	sf::RenderWindow m_window;
	Map m_map;
	sf::CircleShape shape;
	Character m_character;
	sf::Clock m_moveClock;
};