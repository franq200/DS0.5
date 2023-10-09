#include "enemy.h"
#include "Helper.h"
#include "Character.h"

void Enemy::TryKill(Character& character)
{
	if (IsDead())
	{
		Kill(character);
	}
}

void Enemy::Attack(Character& character)
{
	if (IsOpponentInRange(character.getPosition()))
	{
		if (!m_isAttackClockRestarted)
		{
			m_attackClock.restart();
			m_isAttackClockRestarted = true;
		}
		if (m_attackClock.getElapsedTime().asMilliseconds() >= speed::enemyAttackSpeed)
		{
			m_attackClock.restart();
			character.LossHp(m_attackDamage * character::damageTakenScaling);
		}
	}
	else if (m_isAttackClockRestarted)
	{
		m_isAttackClockRestarted = false;
	}
}

void Enemy::MakeMove(const sf::Vector2f& characterPos, const std::vector<std::vector<bool>>& map)
{
	if (m_moveClock.getElapsedTime().asMilliseconds() > speed::enemy)
	{
		if (m_movesCounter == 0)
		{
			m_path = m_aStar.FindShortestPath(position::GetMapIndexesFromPosition(characterPos), position::GetMapIndexesFromPosition(getPosition()), map);
		}
		if (!m_path.empty())
		{
			sf::Vector2f movePos = position::GetPositionFromMapIndexes({ static_cast<size_t>(m_path[m_path.size() - 1].x), static_cast<size_t>(m_path[m_path.size() - 1].y) });
			setPosition(movePos);
			UpdateHpBarPos();
			m_path.pop_back();
		}
		if (m_movesCounter == 2)
		{
			m_movesCounter = 0;
		}
		else
		{
			m_movesCounter++;
		}
		m_moveClock.restart();
	}
}

void Enemy::UpdateHpBarPos()
{
	m_hpBar.SetPosition(getPosition());
}
