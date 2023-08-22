#pragma once
#include <SFML/Graphics.hpp>
#include "Moveable.h"
#include "Fightable.h"

class Character : public sf::Sprite, public Moveable, public Fightable
{
public:
	void Init(sf::Vector2f spawnPos);
	void MakeMove(const sf::Vector2f& moveValue);
	void Attack() override;
	int GetElapsedTimeAsMilliseconds() const;
private:
	void WalkAnimation();
	sf::Clock m_moveClock;
	//void AttackAnimation() override;
};

