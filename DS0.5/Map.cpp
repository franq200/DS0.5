#include "Map.h"
#include <fstream>
#include <string>

void Map::Init(Character& character)
{
	LoadMap(character);
}

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

bool Map::IsAbleToMove(const sf::Vector2f& posAfterMove)
{
	for (int y = 0; y < m_map.size(); ++y)
	{
		for (int x = 0; x < m_map[y].size(); ++x)
		{
			if (m_map[y][x].GetState() == CellState::Filled)
			{
				sf::Vector2f cellPos = m_map[y][x].getPosition();
				if (std::abs(posAfterMove.x - cellPos.x) <= 50.f && std::abs(posAfterMove.y - cellPos.y) <= 50.f)
				{
					return false;
				}
			}
		}
	}
	return true;
}

void Map::LoadMap(Character& character)
{
	std::ifstream file;
	file.open("maps\\map.txt");
	std::string line;

	while (getline(file, line))
	{
		std::vector<Cell> row;
		float cellHeight = 50.f;
		float cellWidth = 50.f;
		for (int i = 0; i < line.size(); ++i)
		{
			if (line[i] == '1')
			{
				row.push_back(Cell({ cellWidth, cellHeight }, {i * cellWidth / 2, m_map.size() * cellHeight}, CellState::Filled));
			}
			else if (line[i] == '0')
			{
				row.push_back(Cell({ cellWidth, cellHeight }, { i * cellWidth / 2, m_map.size() * cellHeight }, CellState::Empty));
			}
			else if (line[i] == 'M')
			{
				row.push_back(Cell({ cellWidth, cellHeight }, { i * cellWidth / 2, m_map.size() * cellHeight }, CellState::Empty));
				character.Init({ i * cellWidth / 2, m_map.size() * cellHeight });
			}
		}

		m_map.push_back(row);
	}
}
