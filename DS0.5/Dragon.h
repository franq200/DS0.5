#pragma once
#include "enemy.h"

class Dragon : public Enemy
{
public:
	void Init(const sf::Vector2f& spawnPos) override;
};

