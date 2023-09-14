#include "Map.h"
#include "Helper.h"

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

bool Map::IsCollisionWithCharacter(const sf::Vector2f& posAfterMove, const std::vector<CellState>& forbiddenStates)
{
	auto [xInt, yInt] = position::GetMapIndexesFromPosition({ posAfterMove.x, posAfterMove.y });
	float x = static_cast<float>(xInt);
	float y = static_cast<float>(yInt);
	//CellState cellState = m_map[y][x].GetState();
	std::vector<sf::Vector2f> characterPositions;
	characterPositions.push_back({ x, y });
	if (static_cast<int>(posAfterMove.x) % static_cast<int>(size::cellSize) != 0 && static_cast<int>(posAfterMove.y) % static_cast<int>(size::cellSize) != 0)
	{
		characterPositions.push_back({ x + 1, y });
		characterPositions.push_back({ x, y + 1});
		characterPositions.push_back({ x + 1, y + 1});
	}
	else if (static_cast<int>(posAfterMove.x) % static_cast<int>(size::cellSize) != 0)
	{
		characterPositions.push_back({ x + 1, y });
	}
	else if (static_cast<int>(posAfterMove.y) % static_cast<int>(size::cellSize) != 0)
	{
		characterPositions.push_back({ x, y + 1 });
	}
	for (int i = 0; i < characterPositions.size(); i++)
	{
		CellState cellState = m_map[characterPositions[i].y][characterPositions[i].x].GetState();
		if (std::any_of(forbiddenStates.begin(), forbiddenStates.end(), [cellState](auto state) {return cellState == state; }))
		{
			return IsCollisionWithCell({characterPositions[i].x * size::cellSize, characterPositions[i].y * size::cellSize}, posAfterMove);
		}
	}
	return false;
	//return std::any_of(forbiddenStates.begin(), forbiddenStates.end(), [characterPositions](auto state) {return std::any_of(characterPositions.begin(), characterPositions.end(), [state](auto characterPos) { return characterPos.GetState() == state; }; });
}

const sf::Vector2f& Map::GetCharacterSpawnPos() const
{
	return m_spawnPosition;
}

const std::vector<std::vector<bool>>& Map::GetRawMap() const
{
	return m_rawMap;
}

const sf::Vector2f& Map::GetGoblinSpawnPos() const
{
	return sf::Vector2f();
}

const sf::Vector2f& Map::GetWarriorSpawnPos() const
{
	return sf::Vector2f();
}

const sf::Vector2f& Map::GetDragonSpawnPos() const
{
	return sf::Vector2f();
}

void Map::TryOpenGate(const sf::Vector2f& characterPos, const sf::Vector2f& characterScale)
{
}

bool Map::IsCollisionWithCell(const sf::Vector2f& cellPos, const sf::Vector2f& characterPos)
{
	return (std::abs(characterPos.x - cellPos.x) <= size::cellSize && std::abs(characterPos.y - cellPos.y) <= size::cellSize);
}