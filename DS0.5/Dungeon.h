#pragma once
#include "Map.h"
#include "Character.h"

class Dungeon : public Map
{
public:
	void LoadMap(Character& character) override;
	std::vector<std::vector<bool>> GetRawMap() const;
private:
	std::vector<std::vector<bool>> m_rawMap;
};

