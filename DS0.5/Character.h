#pragma once
#include <SFML/Graphics.hpp>
#include "Moveable.h"
#include "Fightable.h"

class Enemy;

class Character : public Moveable, public Fightable
{
public:
	Character();
	void Teleport(const sf::Vector2f& newPosition);
	sf::Vector2f getPosition() const;
	bool IsAbleToAttack();
	void Init(sf::Vector2f spawnPos);
	void MakeMove(const sf::Vector2f& moveValue);
	void Attack(Enemy& enemy);
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
	bool m_isAbleToAttack;
	sf::Clock m_moveClock;
	sf::Vector2f m_spawnPos;
};

