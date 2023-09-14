#include "Dungeon.h"
#include "Helper.h"
#include <fstream>
#include <string>

void Dungeon::LoadMap()
{
	std::ifstream file;
	file.open("maps\\dungeon1.txt");
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
			else if (line[i] == '2')
			{
				row.push_back(Cell({ size::cellSize, size::cellSize }, { i * size::cellSize / 2, m_map.size() * size::cellSize }, CellState::Gate));
				rawRow.push_back(false);
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
			else if (line[i] == 'W')
			{
				row.push_back(Cell({ size::cellSize, size::cellSize }, { i * size::cellSize / 2, m_map.size() * size::cellSize }, CellState::Empty));
				rawRow.push_back(true);
				m_warriorSpawnPos = { i * size::cellSize / 2, m_map.size() * size::cellSize };
			}
			else if (line[i] == 'D')
			{
				row.push_back(Cell({ size::cellSize, size::cellSize }, { i * size::cellSize / 2, m_map.size() * size::cellSize }, CellState::Empty));
				rawRow.push_back(true);
				m_dragonSpawnPos = { i * size::cellSize / 2, m_map.size() * size::cellSize };
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

const sf::Vector2f& Dungeon::GetGoblinSpawnPos() const
{
	return m_goblinSpawnPos;
}

const sf::Vector2f& Dungeon::GetWarriorSpawnPos() const
{
	return m_warriorSpawnPos;
}

const sf::Vector2f& Dungeon::GetDragonSpawnPos() const
{
	return m_dragonSpawnPos;
}

void Dungeon::TryOpenGate(const sf::Vector2f& characterPos, const sf::Vector2f& characterScale)
{
	for (int x = 0; x < m_map.size(); x++)
	{
		for (int y = 0; y < m_map[x].size(); y++)
		{
			if (IsCollisionWithCell(m_map[x][y].getPosition(), characterPos))
			{
				Open(x, y);
			}
		}
	}
}

void Dungeon::Open(int x, int y)
{
	m_map[x][y].ChangeState(CellState::Empty);
	m_rawMap[x][y] = true;
	const auto [rX, rY] = position::Right(x, y);
	if (m_map[rX][rY].GetState() == CellState::Gate)
	{
		Open(rX, rY);
	}
	const auto [lX, lY] = position::Left(x, y);
	if (m_map[lX][lY].GetState() == CellState::Gate)
	{
		Open(lX, lY);
	}
	const auto [tX, tY] = position::Top(x, y);
	if (m_map[tX][tY].GetState() == CellState::Gate)
	{
		Open(tX, tY);
	}
	const auto [bX, bY] = position::Bottom(x, y);
	if (m_map[bX][bY].GetState() == CellState::Gate)
	{
		Open(bX, bY);
	}
}
