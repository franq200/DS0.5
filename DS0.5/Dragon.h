#pragma once
#include "enemy.h"
#include <SFML/Graphics.hpp>

class Character;

class Dragon : public Enemy
{
public:
	Dragon(std::unique_ptr<IHpBar> hpBar);
private:
	void Kill(Character& character) override;
};

