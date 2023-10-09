#include "Parser.h"
#include "Helper.h"

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

class ParserCommandWithPosition : public ParserCommand
{
public:
	virtual MoveableObjPosition GetPosition() const = 0;
protected:
	sf::Vector2f position;
};

class ParserFilledCellCommand : public ParserCommand
{
public:
	LineParseResult execute(size_t mapSize, int i) override
	{
		return { Cell({ConvertMapIndexPositionToPixelPosition(mapSize, i)}, CellState::Filled), false };
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

class ParserGateCellCommand : public ParserCommand
{
public:
	LineParseResult execute(size_t mapSize, int i) override
	{
		return { Cell({ ConvertMapIndexPositionToPixelPosition(mapSize, i) }, CellState::Gate), false };
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

class ParserCharacterCellCommand : public ParserCommandWithPosition
{
public:
	LineParseResult execute(size_t mapSize, int i) override
	{
		position = ConvertMapIndexPositionToPixelPosition(mapSize, i);
		return { Cell({ ConvertMapIndexPositionToPixelPosition(mapSize, i) }, CellState::Empty), true };
	}

	MoveableObjPosition GetPosition() const
	{
		return { position, ObjType::Character };
	}
};

class ParserGoblinCellCommand : public ParserCommandWithPosition
{
public:
	LineParseResult execute(size_t mapSize, int i) override
	{
		position = ConvertMapIndexPositionToPixelPosition(mapSize, i);
		return { Cell({ ConvertMapIndexPositionToPixelPosition(mapSize, i) }, CellState::Empty), true };
	}

	MoveableObjPosition GetPosition() const
	{
		return { position, ObjType::Goblin };
	}
};

class ParserWarriorCellCommand : public ParserCommandWithPosition
{
public:
	LineParseResult execute(size_t mapSize, int i) override
	{
		position = ConvertMapIndexPositionToPixelPosition(mapSize, i);
		return { Cell({ ConvertMapIndexPositionToPixelPosition(mapSize, i) }, CellState::Empty), true };
	}

	MoveableObjPosition GetPosition() const
	{
		return { position, ObjType::Warrior };
	}
};

class ParserDragonCellCommand : public ParserCommandWithPosition
{
public:
	LineParseResult execute(size_t mapSize, int i) override
	{
		position = ConvertMapIndexPositionToPixelPosition(mapSize, i);
		return { Cell({ ConvertMapIndexPositionToPixelPosition(mapSize, i) }, CellState::Empty), true };
	}

	MoveableObjPosition GetPosition() const
	{
		return { position, ObjType::Dragon };
	}
};

Parser::Parser(std::vector<std::vector<Cell>>& map, std::vector<std::vector<bool>>& rawMap)
	: map(map), rawMap(rawMap)
{
	commands['1'] = std::make_unique<ParserFilledCellCommand>();
	commands['0'] = std::make_unique<ParserEmptyCellCommand>();
	commands['2'] = std::make_unique<ParserGateCellCommand>();
	commands['V'] = std::make_unique<ParserTeleportCellCommand>();
	commands['M'] = std::make_unique<ParserCharacterCellCommand>();
	commands['G'] = std::make_unique<ParserGoblinCellCommand>();
	commands['W'] = std::make_unique<ParserWarriorCellCommand>();
	commands['D'] = std::make_unique<ParserDragonCellCommand>();
}

Parser::~Parser()
{
}

void Parser::Parse(char command, int i)
{

	auto commandIt = commands.find(command);
	if (commandIt != commands.end())
	{
		auto [_row, _rawRow] = commandIt->second->execute(map.size(), i);
		row.emplace_back(_row);
		rawRow.emplace_back(_rawRow);
	}
}

void Parser::EndRow()
{
	map.push_back(row);
	rawMap.push_back(rawRow);
	
	row.clear();
	rawRow.clear();
}

std::vector<MoveableObjPosition> Parser::GetPositions() const
{
	std::vector<MoveableObjPosition> results;
	for (auto& [key, obj] : commands)
	{
		if (auto* moveableObj = dynamic_cast<ParserCommandWithPosition*>(obj.get()))
		{
			results.emplace_back(moveableObj->GetPosition());
		}
	}
	return results;
}