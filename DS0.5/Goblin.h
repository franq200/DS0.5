#pragma once
#include "enemy.h"
#include <SFML/Graphics.hpp>

class Character;

class Goblin : public Enemy
{
public:
	void Init(const sf::Vector2f& spawnPos) override;
	void Restart() override;
private:
	void Kill(Character& character) override;
};