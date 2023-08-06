#pragma once
#include "Map.h"
#include "Character.h"

class Dungeon : public Map
{
public:
	void LoadMap(Character& character) override;
private:
};

