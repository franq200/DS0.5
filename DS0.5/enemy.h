#pragma once
#include <SFML/Graphics.hpp>
#include "Fightable.h"
#include "Moveable.h"

class Character;

class Enemy : public Fightable, public Moveable
{
public:
	virtual void Init(const sf::Vector2f& spawnPos) = 0;
	virtual void Restart() = 0;
	void TryKill(Character& character);
	void Attack(Character& character);
	void MakeMove(const sf::Vector2f& characterPos, const std::vector<std::vector<bool>>& map);
	void UpdateHpBarPos() override;
protected:
	virtual void Kill(Character& character) = 0;
	sf::Vector2f m_spawnPos;
	sf::Clock m_moveClock;
	int m_movesCounter = 0;
	std::vector<sf::Vector2f> m_pathToCharacter;
	bool m_isAttackClockRestarted = false;
	float m_attackDamage = 0;
private:
};