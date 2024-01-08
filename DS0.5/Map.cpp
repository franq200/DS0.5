#include "Map.h"

bool IsOccupiedDownSquare(const sf::Vector2f& posAfterMove)
{
	return static_cast<int>(posAfterMove.y) % static_cast<int>(size::cellSize) != 0;
}

bool IsOccupiedRightSquare(const sf::Vector2f& posAfterMove)
{
	return static_cast<int>(posAfterMove.x) % static_cast<int>(size::cellSize) != 0;
}

bool IsOccupiedDownAndRightSquare(const sf::Vector2f& posAfterMove)
{
	return static_cast<int>(posAfterMove.x) % static_cast<int>(size::cellSize) != 0 && static_cast<int>(posAfterMove.y) % static_cast<int>(size::cellSize) != 0;
}

std::vector<sf::Vector2f> prepareOccupiedPositionsByCharacter(const sf::Vector2f& posAfterMove, float x, float y)
{
	std::vector<sf::Vector2f> characterPositions;
	characterPositions.push_back({ x, y });
	if (IsOccupiedDownAndRightSquare(posAfterMove))
	{
		characterPositions.push_back({ x + 1, y });
		characterPositions.push_back({ x, y + 1 });
		characterPositions.push_back({ x + 1, y + 1 });
	}
	else if (IsOccupiedRightSquare(posAfterMove))
	{
		characterPositions.push_back({ x + 1, y });
	}
	else if (IsOccupiedDownSquare(posAfterMove))
	{
		characterPositions.push_back({ x, y + 1 });
	}

	return characterPositions;
}

void Map::Update(Character& character)
{
}

void Map::Restart()
{
}

const sf::Vector2f& Map::GetCharacterSpawnPos() const
{
	return m_characterSpawnPos;
}

std::optional<std::pair<float, float>> Map::GetCollisionSquare(const sf::Vector2f& posAfterMove, const std::vector<CellState>& forbiddenStates)
{
	auto [xInt, yInt] = position::GetMapIndexesFromPosition({ posAfterMove.x, posAfterMove.y });
	float x = static_cast<float>(xInt);
	float y = static_cast<float>(yInt);

	std::vector<sf::Vector2f> characterPositions = prepareOccupiedPositionsByCharacter(posAfterMove, x, y);
	
	for (const auto[x, y] : characterPositions)
	{ 
		CellState cellState = m_map[static_cast<int>(y)][static_cast<int>(x)].GetState();
		if (std::any_of(forbiddenStates.begin(), forbiddenStates.end(), [cellState](auto state) {return cellState == state; }))
		{
			bool isCollision = IsCollisionWithCell({x * size::cellSize, y * size::cellSize}, posAfterMove);
			if (isCollision)
			{
				return std::make_optional < std::pair<float, float>>(x, y);
			}
		}
	}
	return std::nullopt;
}

void Map::MakeEnemiesMove(const sf::Vector2f& characterPos)
{
}

void Map::Init()
{
}

void Map::DrawMap(sf::RenderWindow& window)
{
	for (int i = 0; i < m_map.size(); ++i)
	{
		for (int j = 0; j < m_map[i].size(); ++j)
		{
			window.draw(m_map[i][j]);
		}
	}
}

bool Map::IsCollisionWithCell(const sf::Vector2f& cellPos, const sf::Vector2f& characterPos)
{
	return (std::abs(characterPos.x - cellPos.x) <= size::cellSize && std::abs(characterPos.y - cellPos.y) <= size::cellSize);
}