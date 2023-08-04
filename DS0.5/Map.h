#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Cell.h"
#include "Character.h"

class Map
{
public:
	void Init(Character& character);
	void Draw(sf::RenderWindow& window);
	bool IsAbleToMove(const sf::Vector2f& posAfterMove);
private:
	void LoadMap(Character& character);
	std::vector<std::vector<Cell>> m_map;
};

