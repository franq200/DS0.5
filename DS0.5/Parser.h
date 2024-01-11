#pragma once
#include <map>
#include <memory>
#include "Cell.h"

class ParserCommand;

struct Textures
{
	sf::Texture& wall = textures::wall;
	sf::Texture& ground = textures::grass;
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

class Parser
{
public:
	Parser(const Textures& textures);
	~Parser();
	void Parse(char command, int i, uint16_t mapSize);
	void EndRow(std::vector<std::vector<Cell>>& map, std::vector<std::vector<bool>>& rawMap);
	std::vector<MoveableObjPosition> GetPositions() const;

protected:
	Textures m_textures;
private:
	std::map<char, std::unique_ptr<ParserCommand>> commands;
	std::vector<Cell> m_row;
	std::vector<bool> m_rawRow;
};

