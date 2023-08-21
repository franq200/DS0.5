#include "Dungeon.h"
#include "Helper.h"
#include <fstream>
#include <string>

void Dungeon::LoadMap(Character& character)
{
	std::ifstream file;
	file.open("maps\\dungeon.txt");
	std::string line;

	while (getline(file, line))
	{
		std::vector<Cell> row;
		std::vector<bool> rawRow;
		for (int i = 0; i < line.size(); ++i)
		{
			if (line[i] == '1')
			{
				row.push_back(Cell({ size::cellSize, size::cellSize }, { i * size::cellSize / 2, m_map.size() * size::cellSize }, CellState::Filled));
				rawRow.push_back(false);
			}
			else if (line[i] == '0')
			{
				row.push_back(Cell({ size::cellSize, size::cellSize }, { i * size::cellSize / 2, m_map.size() * size::cellSize }, CellState::Empty));
				rawRow.push_back(true);
			}
			else if (line[i] == 'M')
			{
				row.push_back(Cell({ size::cellSize, size::cellSize }, { i * size::cellSize / 2, m_map.size() * size::cellSize }, CellState::Empty));
				rawRow.push_back(true);
				m_spawnPosition = { i * size::cellSize / 2, m_map.size() * size::cellSize };
			}
			else if (line[i] == 'G')
			{
				row.push_back(Cell({ size::cellSize, size::cellSize }, { i * size::cellSize / 2, m_map.size() * size::cellSize }, CellState::Empty));
				rawRow.push_back(true);
				m_goblinSpawnPos = { i * size::cellSize / 2, m_map.size() * size::cellSize };
			}
			else if (line[i] == 'V')
			{
				row.push_back(Cell({ size::cellSize, size::cellSize }, { i * size::cellSize / 2, m_map.size() * size::cellSize }, CellState::Teleport));
				rawRow.push_back(true);
			}
		}
		m_map.push_back(row);
		m_rawMap.push_back(rawRow);
	}
}

const std::vector<std::vector<bool>>& Dungeon::GetRawMap() const
{
	return m_rawMap;
}
