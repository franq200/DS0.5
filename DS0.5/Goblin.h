#pragma once
#include "enemy.h"
#include <SFML/Graphics.hpp>
#include "Character.h"

class Goblin : public Enemy
{
public:
	void Init(const sf::Vector2f& spawnPos) override;
};