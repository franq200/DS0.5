#include "Village.h"
#include <fstream>
#include <string>
#include "Parser.h"

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
	std::ifstream file("maps\\map.txt");
	std::string line;

	Parser parser(m_map, m_rawMap);
	while (getline(file, line))
	{
		std::vector<Cell> row;
		std::vector<bool> rawRow;
		for (int i = 0; i < line.size(); ++i)
		{
			parser.Parse(line[i], i);
		}
		parser.EndRow();
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

void Village::Init()
{
}
