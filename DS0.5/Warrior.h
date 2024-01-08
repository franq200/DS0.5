#pragma once
#include "enemy.h"
#include <SFML/Graphics.hpp>

class Character;

class Warrior : public Enemy
{
public:
	Warrior();
private:
	void Kill(Character& character) override;
};

