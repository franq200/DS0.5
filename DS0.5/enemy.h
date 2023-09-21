#pragma once
#include <SFML/Graphics.hpp>
#include "AStar.h"
#include "Fightable.h"
#include "Moveable.h"

class Character;

class Enemy : public Fightable, public Moveable
{
public:
	virtual void Init(const sf::Vector2f& spawnPos) = 0;
	bool Attack(Character& character);
	void MakeMove(const sf::Vector2f& characterPos, const std::vector<std::vector<bool>>& map);
	void Restart(sf::Vector2f spawnPos);
	void UpdateHpBarPos() override;
	float GetAttackDamage() const;
protected:
	sf::Clock m_moveClock;
	int m_movesCounter = 0;
	std::vector<sf::Vector2f> m_path;
	std::vector<sf::Vector2f> m_pathToCharacter;
	bool m_isAttackClockRestarted = false;
	float m_attackDamage = 0;
private:
	AStar m_aStar;
};