#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Cell.h"
#include "Character.h"

class Map
{
public:
	void Draw(sf::RenderWindow& window);
	bool IsCollisionWithCharacter(sf::Vector2f posAfterMove, CellState cellsToCheck, const float& characterXScale);
	virtual void LoadMap(Character& character) = 0;
protected:
	bool IsCollisionWithCell(const sf::Vector2f& cellPos, const sf::Vector2f& characterPos);
	std::vector<std::vector<Cell>> m_map;
};

