#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Cell.h"
#include "Character.h"
#include "Goblin.h"

class Map
{
public:
	virtual void LoadMap() = 0;
	void Draw(sf::RenderWindow& window);
	bool IsCollisionWithCharacter(sf::Vector2f posAfterMove, CellState cellsToCheck, const float& characterXScale);
	sf::Vector2f GetCharacterSpawnPos() const;
	sf::Vector2f GetGoblinSpawnPos() const;
	virtual const std::vector<std::vector<bool>>& GetRawMap() const = 0;
protected:
	bool IsCollisionWithCell(const sf::Vector2f& cellPos, const sf::Vector2f& characterPos);
	std::vector<std::vector<Cell>> m_map;
	sf::Vector2f m_spawnPosition;
	sf::Vector2f m_goblinSpawnPos;
	std::vector<std::vector<bool>> m_rawMap;
};

