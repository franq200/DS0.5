#include "Village.h"
#include <fstream>
#include <string>

void Village::MapInit()
{
	LoadMap();
	Init();
}

void Village::Update(Character& character)
{
}

void Village::Draw(sf::RenderWindow& window)
{
	DrawMap(window);
}

void Village::Restart()
{
}

void Village::LoadMap()
{
	std::ifstream file;
	file.open("maps\\map.txt");
	std::string line;

	while (getline(file, line))
	{
		std::vector<Cell> row;
		std::vector<bool> rawRow;
		float cellHeight = 50.f;
		float cellWidth = 50.f;
		for (int i = 0; i < line.size(); ++i)
		{
			if (line[i] == '1')
			{
				row.push_back(Cell({ cellWidth, cellHeight }, { i * cellWidth / 2, m_map.size() * cellHeight }, CellState::Filled));
				rawRow.push_back(false);
			}
			else if (line[i] == '0')
			{
				row.push_back(Cell({ cellWidth, cellHeight }, { i * cellWidth / 2, m_map.size() * cellHeight }, CellState::Empty));
				rawRow.push_back(true);
			}
			else if (line[i] == 'S')
			{
				row.push_back(Cell({ cellWidth, cellHeight }, { i * cellWidth / 2, m_map.size() * cellHeight }, CellState::Empty));
				rawRow.push_back(true);
				m_characterSpawnPos = { i * cellWidth / 2, m_map.size() * cellHeight };
			}
			else if (line[i] == 'M')
			{
				row.push_back(Cell({ cellWidth, cellHeight }, { i * cellWidth / 2, m_map.size() * cellHeight }, CellState::Empty));
				rawRow.push_back(true);
				m_characterSpawnPos = { i * cellWidth / 2, m_map.size() * cellHeight };
			}
			else if (line[i] == 'D')
			{
				row.push_back(Cell({ cellWidth, cellHeight }, { i * cellWidth / 2, m_map.size() * cellHeight }, CellState::Teleport));
				rawRow.push_back(true);
			}
		}

		m_map.push_back(row);
		m_rawMap.push_back(rawRow);
	}
}

void Village::Init()
{
}
