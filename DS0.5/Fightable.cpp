#include "Fightable.h"
#include "IClock.h"
#include "HpBar.h"

Fightable::Fightable(Damage attackDamage, Hp startHp, AttackRange attackRange, AttackSpeed attackSpeed, std::unique_ptr<IHpBar> hpBar, std::unique_ptr<IClock> clock):
	m_attackDamage(attackDamage), m_startHp(startHp), m_attackRange(attackRange), m_attackSpeed(attackSpeed), m_hpBar(std::move(hpBar)), m_attackClock(std::move(clock))
{
}

void Fightable::LossHp(float lostHp)
{
	m_hpBar->LossHp(lostHp);
}

void Fightable::GainHp(float gainedHp)
{
	m_hpBar->GainHp(gainedHp);
}

bool Fightable::IsDead()
{
	return m_hpBar->IsDead();
}

void Fightable::Draw(sf::RenderWindow& window)
{
	m_hpBar->Draw(window);
	window.draw(*this);
}

void Fightable::SetHp(float newHp)
{
	m_hpBar->SetNewMaxHp(newHp);
}

void Fightable::SetDamegeTakenScaling(DamageScale scale)
{
	m_damageTakenScaling = scale;
}

void Fightable::SetDamageGivenScaling(DamageScale scale)
{
	m_damageGivenScaling = scale;
}

DamageScale Fightable::GetDamageTakenScaling() const
{
	return m_damageTakenScaling;
}

bool Fightable::IsOpponentInRange(const sf::Vector2f& opponentPos, const sf::Vector2f& pos)
{
	return (std::abs(pos.x - opponentPos.x) <= m_attackRange && std::abs(pos.y - opponentPos.y) <= m_attackRange);
}
