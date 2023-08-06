#include "Village.h"
#include <fstream>
#include <string>

void Village::LoadMap(Character& character)
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
				row.push_back(Cell({ cellWidth, cellHeight }, { i * cellWidth / 2, m_map.size() * cellHeight }, CellState::Filled));
			}
			else if (line[i] == '0')
			{
				row.push_back(Cell({ cellWidth, cellHeight }, { i * cellWidth / 2, m_map.size() * cellHeight }, CellState::Empty));
			}
			else if (line[i] == 'M')
			{
				row.push_back(Cell({ cellWidth, cellHeight }, { i * cellWidth / 2, m_map.size() * cellHeight }, CellState::Empty));
				character.setPosition({ i * cellWidth / 2, m_map.size() * cellHeight });
			}
			else if (line[i] == 'D')
			{
				row.push_back(Cell({ cellWidth, cellHeight }, { i * cellWidth / 2, m_map.size() * cellHeight }, CellState::Teleport));
			}
		}

		m_map.push_back(row);
	}
}
