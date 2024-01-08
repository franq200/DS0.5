#pragma once
#include <map>
#include <memory>
#include "Cell.h"

class ParserCommand;

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

class Parser
{
public:
	Parser();
	~Parser();
	void Parse(char command, int i, uint16_t mapSize);
	void EndRow(std::vector<std::vector<Cell>>& map, std::vector<std::vector<bool>>& rawMap);
	std::vector<MoveableObjPosition> GetPositions() const;
private:
	std::map<char, std::unique_ptr<ParserCommand>> commands;
	std::vector<Cell> m_row;
	std::vector<bool> m_rawRow;
	Textures m_textures;
};

