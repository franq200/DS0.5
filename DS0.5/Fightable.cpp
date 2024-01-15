#include "Fightable.h"

Fightable::Fightable(Damage attackDamage, Hp startHp, AttackRange attackRange, AttackSpeed attackSpeed):
	m_attackDamage(attackDamage), m_startHp(startHp), m_attackRange(attackRange), m_attackSpeed(attackSpeed)
{
}

void Fightable::LossHp(float lostHp)
{
	m_hpBar.LossHp(lostHp);
}

void Fightable::GainHp(float gainedHp)
{
	m_hpBar.GainHp(gainedHp);
}

bool Fightable::IsDead()
{
	return m_hpBar.IsDead();
}

void Fightable::Draw(sf::RenderWindow& window)
{
	m_hpBar.Draw(window);
	window.draw(*this);
}

void Fightable::SetHp(float newHp)
{
	m_hpBar.IncreaseMaxHp(newHp);
}

bool Fightable::IsOpponentInRange(const sf::Vector2f& opponentPos, const sf::Vector2f& pos)
{
	return (std::abs(pos.x - opponentPos.x) <= m_attackRange && std::abs(pos.y - opponentPos.y) <= m_attackRange);
}
