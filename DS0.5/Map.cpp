#include "Map.h"

void Map::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < m_map.size(); ++i)
	{
		for (int j = 0; j < m_map[i].size(); ++j)
		{
			window.draw(m_map[i][j]);
		}
	}
}

bool Map::IsCollisionWithCharacter(sf::Vector2f posAfterMove, const std::vector<CellState>& cellsToCheck, const float& characterXScale)
{
	for (int y = 0; y < m_map.size(); ++y)
	{
		for (int x = 0; x < m_map[y].size(); ++x)
		{
			for (int i = 0; i < cellsToCheck.size(); i++)
			{
				if (m_map[y][x].GetState() == cellsToCheck[i])
				{
					if (IsCollisionWithCell(m_map[y][x].getPosition(), posAfterMove, {characterXScale, 0.f}))
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

const sf::Vector2f Map::GetCharacterSpawnPos() const
{
	return m_spawnPosition;
}

const std::vector<std::vector<bool>>& Map::GetRawMap() const
{
	return m_rawMap;
}

const sf::Vector2f Map::GetGoblinSpawnPos() const
{
	return sf::Vector2f();
}

const sf::Vector2f Map::GetWarriorSpawnPos() const
{
	return sf::Vector2f();
}

const sf::Vector2f Map::GetDragonSpawnPos() const
{
	return sf::Vector2f();
}

void Map::TryOpenGate(const sf::Vector2f& characterPos, const sf::Vector2f& characterScale)
{
}

bool Map::IsCollisionWithCell(const sf::Vector2f& cellPos, const sf::Vector2f& characterPos, const sf::Vector2f& scale)
{
	if (scale.x < 0)
	{
		return (std::abs(characterPos.x - 50.f - cellPos.x) <= 50.f && std::abs(characterPos.y - cellPos.y) <= 50.f);
	}
	return (std::abs(characterPos.x - cellPos.x) <= 50.f && std::abs(characterPos.y - cellPos.y) <= 50.f);
}

