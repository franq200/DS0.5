#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>
#include "Cell.h"
#include "Character.h"
#include "Goblin.h"

class Map
{
public:
	virtual void LoadMap() = 0;
	void Draw(sf::RenderWindow& window);
	bool IsCollisionWithCharacter(sf::Vector2f posAfterMove, const std::vector<CellState>& cellsToCheck, const float& characterXScale);
	const sf::Vector2f GetCharacterSpawnPos() const;
	const std::vector<std::vector<bool>>& GetRawMap() const;
	virtual const sf::Vector2f GetGoblinSpawnPos() const;
	virtual const sf::Vector2f GetWarriorSpawnPos() const;
	virtual const sf::Vector2f GetDragonSpawnPos() const;
	virtual void TryOpenGate(const sf::Vector2f& characterPos, const sf::Vector2f& characterScale);
protected:
	bool IsCollisionWithCell(const sf::Vector2f& cellPos, const sf::Vector2f& characterPos, const sf::Vector2f& scale);
	std::vector<std::vector<Cell>> m_map;
	sf::Vector2f m_spawnPosition;
	std::vector<std::vector<bool>> m_rawMap;
};

