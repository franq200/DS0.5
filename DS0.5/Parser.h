#pragma once
#include "Map.h"

struct LineParseResult
{
	Cell cell;
	bool isMoveableCell;
};

enum class ObjType
{
	Character,
	Warrior,
	Goblin,
	Dragon
};

struct MoveableObjPosition
{
	sf::Vector2f position;
	ObjType type;
};

class ParserCommand
{
public:
	virtual LineParseResult execute(size_t mapSize, int i) = 0;
};

class Parser
{
public:
	Parser(std::vector<std::vector<Cell>>& map, std::vector<std::vector<bool>>& rawMap);
	void Parse(char command, int i);
	void EndRow();
	std::vector<MoveableObjPosition> GetPositions() const;

private:
	std::map<char, std::unique_ptr<ParserCommand>> commands;
	std::vector<std::vector<Cell>>& map;
	std::vector<std::vector<bool>>& rawMap;
	std::vector<Cell> row;
	std::vector<bool> rawRow;
};

