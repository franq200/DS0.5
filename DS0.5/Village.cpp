#include "Village.h"
#include <fstream>
#include <string>

namespace
{
	sf::Vector2f ConvertMapIndexPositionToPixelPosition(size_t mapSize, int i)
	{
		return { i * size::cellSize / 2, mapSize * size::cellSize };
	}

	struct LineParseResult
	{
		Cell cell;
		bool isMoveableCell;
	};

	class ParserCommand
	{
	public:
		virtual LineParseResult execute(size_t mapSize, int i) = 0;
	};

	class ParserFilledCellCommand : public ParserCommand
	{
	public:
		LineParseResult execute(size_t mapSize, int i) override
		{
			return { Cell({ ConvertMapIndexPositionToPixelPosition(mapSize, i) }, CellState::Filled), false };
		}
	};

	class ParserEmptyCellCommand : public ParserCommand
	{
	public:
		LineParseResult execute(size_t mapSize, int i) override
		{
			return { Cell({ ConvertMapIndexPositionToPixelPosition(mapSize, i) }, CellState::Empty), true };
		}
	};

	class ParserTeleportCellCommand : public ParserCommand
	{
	public:
		LineParseResult execute(size_t mapSize, int i) override
		{
			return { Cell({ ConvertMapIndexPositionToPixelPosition(mapSize, i) }, CellState::Teleport), true };
		}
	};

	class ParserCommandWithPosition : public ParserCommand
	{
	public:
		virtual sf::Vector2f GetPosition() const = 0;
	protected:
		sf::Vector2f position;
	};

	class ParserCharacterCellCommand : public ParserCommandWithPosition
	{
	public:
		LineParseResult execute(size_t mapSize, int i) override
		{
			position = ConvertMapIndexPositionToPixelPosition(mapSize, i);
			return { Cell({ ConvertMapIndexPositionToPixelPosition(mapSize, i) }, CellState::Empty), true };
		}

		sf::Vector2f GetPosition() const
		{
			return position;
		}
	};

	class Parser
	{
	public:
		Parser(std::vector<std::vector<Cell>>& map, std::vector<std::vector<bool>> rawMap)
			: map(map), rawMap(rawMap)
		{
			commands['1'] = std::make_unique<ParserFilledCellCommand>();
			commands['0'] = std::make_unique<ParserEmptyCellCommand>();
			commands['D'] = std::make_unique<ParserTeleportCellCommand>();
			commands['M'] = std::make_unique<ParserCharacterCellCommand>();
		}

		void Parse(char command, int i)
		{
			auto commandIt = commands.find(command);
			if (commandIt != commands.end())
			{
				auto [_row, _rawRow] = commandIt->second->execute(map.size(), i);
				row.emplace_back(_row);
				rawRow.emplace_back(_rawRow);
			}
		}

		void EndRow()
		{
			map.emplace_back(row);
			rawMap.emplace_back(rawRow);

			row.clear();
			rawRow.clear();
		}

		sf::Vector2f GetPosition() const
		{
			for (auto& [key, obj] : commands)
			{
				if (auto* moveableObj = dynamic_cast<ParserCharacterCellCommand*>(obj.get()))
				{
					return moveableObj->GetPosition();
				}
			}
		}

	private:
		std::map<char, std::unique_ptr<ParserCommand>> commands;
		std::vector<std::vector<Cell>>& map;
		std::vector<std::vector<bool>>& rawMap;
		std::vector<Cell> row;
		std::vector<bool> rawRow;
	};
}


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

	m_characterSpawnPos = parser.GetPosition();
}

void Village::Init()
{
}
