#pragma once
#include "Map.h"
#include <SFML/Graphics.hpp>

class Game
{
public:
	void Init();
	void Update();
private:
	void Draw();
	void Events();
	sf::RenderWindow m_window;
	Map m_map;
	sf::CircleShape shape;
};