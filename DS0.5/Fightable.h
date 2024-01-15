#pragma once
#include <SFML/Graphics.hpp>
#include "HpBar.h"

using Hp = float;
using Damage = float;
using AttackRange = float;
using AttackSpeed = float;

class Fightable : public virtual sf::Sprite
{
public:
	explicit Fightable(Damage attackDamage, Hp startHp, AttackRange attackRange, AttackSpeed attackSpeed);
	void LossHp(float lostHp);
	void GainHp(float gainedHp);
	bool IsDead();
	void Draw(sf::RenderWindow& window);
	void SetHp(float newHp);
	virtual void UpdateHpBarPos() = 0;
protected:
	bool IsOpponentInRange(const sf::Vector2f& opponentPos, const sf::Vector2f& pos);
	sf::Clock m_attackClock;
	HpBar m_hpBar;
	const AttackSpeed m_attackSpeed = 0;
	const Damage m_attackDamage = 0;
	const Hp m_startHp = 0;
	const AttackRange m_attackRange = 0;
};

