#include "enemy.h"
#include "Helper.h"
#include "Character.h"
#include "AStar.h"

Enemy::Enemy(float attackDamage, const sf::Texture& texture, float startHp, float scale):
	Fightable(attackDamage, startHp), m_texture(texture), m_scale(scale)
{
}

void Enemy::Init(const sf::Vector2f& spawnPos)
{
	m_spawnPos = spawnPos;
	setTexture(m_texture);
	setScale(m_scale, m_scale);
	m_moveClock.restart();
	setPosition(m_spawnPos);
	m_hpBar.Init(getPosition(), m_startHp);
}

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
			m_pathToCharacter = aStar::FindShortestPath(position::GetMapIndexesFromPosition(characterPos), position::GetMapIndexesFromPosition(getPosition()), map);
		}
		if (!m_pathToCharacter.empty())
		{
			sf::Vector2f movePos = position::GetPositionFromMapIndexes({ static_cast<size_t>(m_pathToCharacter[m_pathToCharacter.size() - 1].x), static_cast<size_t>(m_pathToCharacter[m_pathToCharacter.size() - 1].y) });
			setPosition(movePos);
			UpdateHpBarPos();
			m_pathToCharacter.pop_back();
		}
		if (m_movesCounter == 5)
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
