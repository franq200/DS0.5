#pragma once
#include "enemy.h"
#include <SFML/Graphics.hpp>

class Character;

class Dragon : public Enemy
{
public:
	Dragon();
	void Restart() override;
private:
	void Kill(Character& character) override;
};

