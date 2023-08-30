#pragma once
#include <SFML/Graphics.hpp>
#include "Moveable.h"

class Character : public sf::Sprite, public Moveable
{
public:
	void Init(sf::Vector2f spawnPos);
	void MakeMove(const sf::Vector2f& moveValue);
	const int GetMoveClockAsMilliseconds() const;
private:
	void WalkAnimation();
	sf::Clock m_moveClock;
};

