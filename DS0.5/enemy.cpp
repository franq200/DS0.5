#include "enemy.h"
#include "Helper.h"

bool Enemy::IsAttackSuccessful(const sf::Vector2f& characterPos, const float& characterScaleX)
{
	if (IsCharacterInRange(characterPos, characterScaleX))
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
			m_path = FindShortestPath(position::GetMapIndexesFromPosition(characterPos), position::GetMapIndexesFromPosition(getPosition()), map);
		}
		if (!m_path.empty())
		{
			sf::Vector2f movePos = position::GetPositionFromMapIndexes({ static_cast<float>(m_path[m_path.size() - 1].x), static_cast<float>(m_path[m_path.size() - 1].y) });
			setPosition(movePos);
			m_hpBar.SetPosition(movePos);
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

void Enemy::LossHp()
{
	m_hp -= 10.f * character::damageScaling;
	m_hpBar.ChangeHpLevel(m_hp);
}

void Enemy::DrawHpBar(sf::RenderWindow& window)
{
	m_hpBar.Draw(window);
}

bool Enemy::IsCharacterInRange(const sf::Vector2f& characterPos, const float& characterScaleX) const
{
	sf::Vector2f pos = getPosition();
	if (characterScaleX < 0.f)
	{
		return (std::abs(pos.x - characterPos.x - 50.f) <= 60 && std::abs(pos.y - characterPos.y) <= 60);
	}
	return (std::abs(pos.x - characterPos.x) <= 60 && std::abs(pos.y - characterPos.y) <= 60);
}

const bool Enemy::IsDead() const
{
	return m_hp <= 0.f;
}

void Enemy::Restart(sf::Vector2f spawnPos)
{
	m_moveClock.restart();
	setPosition(spawnPos);
	m_hp = 100.f;
	m_hpBar.ChangeHpLevel(m_hp);
	m_movesCounter = 0;
}
