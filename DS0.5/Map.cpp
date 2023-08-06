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

bool Map::IsCollisionWithCharacter(sf::Vector2f posAfterMove, CellState cellsToCheck, const float& characterXScale)
{
	if (characterXScale < 0.f)
	{
		posAfterMove.x -= 50.f;
	}
	for (int y = 0; y < m_map.size(); ++y)
	{
		for (int x = 0; x < m_map[y].size(); ++x)
		{
			if (m_map[y][x].GetState() == cellsToCheck)
			{
				if (IsCollisionWithCell(m_map[y][x].getPosition(), posAfterMove))
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool Map::IsCollisionWithCell(const sf::Vector2f& cellPos, const sf::Vector2f& characterPos)
{
	return (std::abs(characterPos.x - cellPos.x) <= 50.f && std::abs(characterPos.y - cellPos.y) <= 50.f);
}
