#pragma once
#include <SFML/Graphics.hpp>
#include "Moveable.h"
#include "Fightable.h"

class Enemy;

class Character : public Moveable, public Fightable
{
public:
	sf::Vector2f getPosition() const;
	void Init(sf::Vector2f spawnPos);
	void MakeMove(const sf::Vector2f& moveValue);
	bool IsAttackSuccessful(const sf::Vector2f& enemyPos);
	int GetMoveClockAsMilliseconds() const;
	void Restart();
	sf::Vector2f GetNextUp() const;
	sf::Vector2f GetNextDown() const;
	sf::Vector2f GetNextLeft() const;
	sf::Vector2f GetNextRight() const;
	void UpdateHpBarPos() override;
	std::vector<sf::Vector2f> GetEveryPossibleMovement() const;
private:
	void Rotate(const sf::Vector2f& moveValue);
	void WalkAnimation();
	bool m_isAbleToAttack;
	sf::Clock m_moveClock;
	std::vector <sf::Texture> m_walkTextures;
	int m_moveCounter = 0;
	sf::Vector2f m_spawnPos;
};

