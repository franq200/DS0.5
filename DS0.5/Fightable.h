#pragma once
#include <SFML/Graphics.hpp>
#include "HpBar.h"

using Hp = float;
using Damage = float;
using AttackRange = float;
using AttackSpeed = float;
using DamageScale = float;

class Fightable : public virtual sf::Sprite
{
public:
	explicit Fightable(Damage attackDamage, Hp startHp, AttackRange attackRange, AttackSpeed attackSpeed, std::unique_ptr<IHpBar> hpBar);
	void LossHp(float lostHp);
	void GainHp(float gainedHp);
	bool IsDead();
	void Draw(sf::RenderWindow& window);
	void SetHp(float newHp);
	virtual void UpdateHpBarPos() = 0;
	void SetDamegeTakenScaling(DamageScale scale);
	void SetDamegeGivenScaling(DamageScale scale);
	DamageScale GetDamageTakenScaling() const;
protected:
	bool IsOpponentInRange(const sf::Vector2f& opponentPos, const sf::Vector2f& pos);
	sf::Clock m_attackClock;
	std::unique_ptr<IHpBar> m_hpBar = nullptr;
	DamageScale m_damageTakenScaling = 1.f;
	DamageScale m_damageGivenScaling = 1.f;
	const AttackSpeed m_attackSpeed = 0;
	const Damage m_attackDamage = 0;
	const Hp m_startHp = 0;
	const AttackRange m_attackRange = 0;
};

