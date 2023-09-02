#pragma once
#include "enemy.h"
#include <SFML/Graphics.hpp>
#include "Character.h"

class Warrior : public Enemy
{
public:
	void Init(sf::Vector2f spawnPos) override;
};

