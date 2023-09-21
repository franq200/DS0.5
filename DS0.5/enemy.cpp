#include "enemy.h"
#include "Helper.h"
#include "Character.h"

bool Enemy::Attack(Character& character)
{
	if (IsOpponentInRange(character.getPosition()))
	{
		if (!m_isAttackClockRestarted)
		{
			m_attackClock.restart();
			m_isAttackClockRestarted = true;
			return false;
		}
		if (m_attackClock.getElapsedTime().asMilliseconds() >= speed::enemyAttackSpeed)
		{
			m_attackClock.restart();
			return true;
		}
	}
	else if (m_isAttackClockRestarted)
	{
		m_isAttackClockRestarted = false;
	}
	return false;
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
			sf::Vector2f movePos = position::GetPositionFromMapIndexes({ static_cast<float>(m_path[m_path.size() - 1].x), static_cast<float>(m_path[m_path.size() - 1].y) });
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

void Enemy::Restart(sf::Vector2f spawnPos)
{
	m_moveClock.restart();
	setPosition(spawnPos);
	m_hpBar.ChangeHpLevel();
	m_movesCounter = 0;
}

void Enemy::UpdateHpBarPos()
{
	m_hpBar.SetPosition(getPosition());
}

float Enemy::GetAttackDamage() const
{
	return m_attackDamage;
}
