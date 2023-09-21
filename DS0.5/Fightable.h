#pragma once
#include <SFML/Graphics.hpp>
#include "HpBar.h"

class Fightable : public virtual sf::Sprite
{
public:
	void LossHp(float lostHp);
	void GainHp(float gainedHp);
	bool IsDead();
	void DrawHpBar(sf::RenderWindow& window);
	void SetHp(float newHp);
	virtual void UpdateHpBarPos() = 0;
protected:
	bool IsOpponentInRange(const sf::Vector2f& opponentPos);
	sf::Clock m_attackClock;
	HpBar m_hpBar;
	float m_attackDamage = 0;
};

