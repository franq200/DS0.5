#include "Fightable.h"

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

void Fightable::DrawHpBar(sf::RenderWindow& window)
{
	m_hpBar.Draw(window);
}

void Fightable::SetHp(float newHp)
{
	m_hpBar.IncreaseMaxHp(newHp);
}

bool Fightable::IsOpponentInRange(const sf::Vector2f& opponentPos)
{
	sf::Vector2f pos = getPosition();
	return (std::abs(pos.x - opponentPos.x) <= 60 && std::abs(pos.y - opponentPos.y) <= 60);
}
