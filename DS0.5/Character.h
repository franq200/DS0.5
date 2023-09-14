#pragma once
#include <SFML/Graphics.hpp>
#include "HpBar.h"
#include "Moveable.h"
#include "Fightable.h"

class Character : public Moveable, public Fightable
{
public:
	sf::Vector2f getPosition() const;
	void Init(sf::Vector2f spawnPos);
	void MakeMove(const sf::Vector2f& moveValue);
	bool IsAttackSuccessful(const sf::Vector2f& opponentPos) override;
	int GetMoveClockAsMilliseconds() const;
	void Restart(const sf::Vector2f& spawnPos);
	sf::Vector2f GetNextUp() const;
	sf::Vector2f GetNextDown() const;
	sf::Vector2f GetNextLeft() const;
	sf::Vector2f GetNextRight() const;
	void UpdateHpBarPos() override;
private:
	void WalkAnimation();
	sf::Clock m_moveClock;
	std::vector <sf::Texture> m_walkTextures;
	int m_moveCounter = 0;
};

