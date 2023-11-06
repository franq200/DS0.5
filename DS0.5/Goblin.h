#pragma once
#include "enemy.h"
#include <SFML/Graphics.hpp>

class Character;

class Goblin : public Enemy
{
public:
	Goblin();
	void Restart() override;
private:
	void Kill(Character& character) override;
};