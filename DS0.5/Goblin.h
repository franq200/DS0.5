#pragma once
#include "enemy.h"
#include <SFML/Graphics.hpp>

class Character;

class Goblin : public Enemy
{
public:
	Goblin(std::unique_ptr<IHpBar> hpBar);
private:
	void Kill(Character& character) override;
};