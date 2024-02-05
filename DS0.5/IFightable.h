#pragma once
#include <SFML/Graphics.hpp>

using Hp = float;
using Damage = float;
using AttackRange = float;
using AttackSpeed = float;
using DamageScale = float;

class IFightable : public virtual sf::Sprite
{
public:
	virtual void LossHp(float lostHp) = 0;
	virtual void GainHp(float gainedHp) = 0;
	virtual bool IsDead() = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;
	virtual void SetHp(float newHp) = 0;
	virtual void UpdateHpBarPos() = 0;
	virtual void SetDamegeTakenScaling(DamageScale scale) = 0;
	virtual void SetDamageGivenScaling(DamageScale scale) = 0;
	virtual DamageScale GetDamageTakenScaling() const = 0;
};

