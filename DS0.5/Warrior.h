#pragma once
#include "enemy.h"
#include <SFML/Graphics.hpp>

class Character;

class Warrior : public Enemy
{
public:
	Warrior(std::unique_ptr<IHpBar> hpBar, std::unique_ptr<IClock> clock);
private:
	void Kill(Character& character) override;
};

