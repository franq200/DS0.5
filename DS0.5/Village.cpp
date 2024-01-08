#include "Village.h"
#include <fstream>
#include <string>
#include "Parser.h"

void Village::MapInit()
{
	LoadMap();
	Init();
	SetTextures();
}

void Village::Draw(sf::RenderWindow& window)
{
	DrawMap(window);
}

void Village::SetTextures()
{
	for (int i = 0; i < m_map.size(); i++)
	{
		for (int j = 0; j < m_map[i].size(); j++)
		{
			m_map[i][j].SetTextures({ textures::wall, textures::grass });
		}
	}
}

void Village::LoadMap()
{
	std::ifstream file("maps\\map.txt");
	std::string line;

	Parser parser;
	while (getline(file, line))
	{
		std::vector<Cell> row;
		std::vector<bool> rawRow;
		for (int i = 0; i < line.size(); ++i)
		{
			parser.Parse(line[i], i, static_cast<uint16_t>(m_map.size()));
		}
		parser.EndRow(m_map, m_rawMap);
	}

	auto positions = parser.GetPositions();

	for (auto& [position, type] : positions)
	{
		switch (type)
		{
		case ObjType::Character:
			m_characterSpawnPos = position;
			break;
		default:
			break;
		}
	}
}