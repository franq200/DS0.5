#pragma once
#include "enemy.h"
#include <SFML/Graphics.hpp>

class Character;

class Goblin : public Enemy
{
public:
	Goblin(std::unique_ptr<HpBar> hpBar);
private:
	void Kill(Character& character) override;
};