#include "Map.h"
#include <fstream>
#include <string>

void Map::Init()
{
	LoadMap();
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

void Map::LoadMap()
{
	std::ifstream file;
	file.open("maps\\map.txt");
	std::string line;

	while (getline(file, line))
	{
		std::vector<sf::RectangleShape> row;
		std::vector<CellType> rawRow;
		float cellHeight = 50.f;
		float cellWidth = 100.f;
		for (int i = 0; i < line.size(); ++i)
		{
			if (line[i] == '1')
			{
				rawRow.push_back(CellType::Filled);
				sf::RectangleShape cell;
				cell.setSize({ cellWidth, cellHeight });
				cell.setFillColor(sf::Color::Red);
				cell.setPosition(i * cellWidth/2, m_map.size() * cellHeight);
				row.push_back(cell);
			}
			else if (line[i] == '0')
			{
				rawRow.push_back(CellType::Empty);
				sf::RectangleShape cell;
				cell.setSize({ cellWidth, cellHeight });
				cell.setFillColor(sf::Color::Green);
				cell.setPosition(i * cellWidth/2, m_map.size() * cellHeight);
				row.push_back(cell);
			}
		}

		m_rawMap.push_back(rawRow);
		m_map.push_back(row);
	}
}
