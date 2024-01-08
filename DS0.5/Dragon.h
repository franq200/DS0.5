#pragma once
#include "enemy.h"
#include <SFML/Graphics.hpp>

class Character;

class Dragon : public Enemy
{
public:
	Dragon();
private:
	void Kill(Character& character) override;
};

