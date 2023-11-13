#include "enemy.h"
#include "Helper.h"
#include "Character.h"
#include "AStar.h"

Enemy::Enemy(float attackDamage, const sf::Texture& texture, float startHp, float scale):
	Fightable(attackDamage, startHp), m_texture(texture), m_scale(scale), Moveable({})
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

void Enemy::PreparePathAndMove(const sf::Vector2f& characterPos, const std::vector<std::vector<bool>>& map)
{
	if (m_moveClock.getElapsedTime().asMilliseconds() > speed::enemy/5)
	{
		if (m_isMoveDone)
		{
			m_pathToCharacter = aStar::FindShortestPath(position::GetMapIndexesFromPosition(characterPos), position::GetMapIndexesFromPosition(getPosition()), map);
			if (!m_pathToCharacter.empty())
			{
				ChooseDirection();
				m_isMoveDone = false;
			}
		}
		else if (!m_isMoveDone)
		{
			if (m_movesCounter == 5)
			{
				m_isMoveDone = true;
				m_movesCounter = 0;
			}
			else
			{
				Move();
				m_movesCounter++;
			}
			
			//sf::Vector2f movePos = position::GetPositionFromMapIndexes({ static_cast<size_t>(m_pathToCharacter[m_pathToCharacter.size() - 1].x), static_cast<size_t>(m_pathToCharacter[m_pathToCharacter.size() - 1].y) });
			//setPosition(movePos);
			//UpdateHpBarPos();
			//m_pathToCharacter.pop_back();
		}
		m_moveClock.restart();
	}
}

void Enemy::UpdateHpBarPos()
{
	m_hpBar.SetPosition(getPosition());
}

void Enemy::Move()
{
	switch (m_moveDirection)
	{
	case Right:
		move(10.f, 0.f);
		break;
	case Left:
		move(-10.f, 0.f);
		break;
	case Down:
		move(0.f, 10.f);
		break;
	case Up:
		move(0.f, -10.f);
	}
}

void Enemy::ChooseDirection()
{
	IndexPosition pos = position::GetMapIndexesFromPosition(getPosition());
	if (m_pathToCharacter.front().y> pos.second)
	{
		m_moveDirection = Direction::Down;
	}
	else
	{
		m_moveDirection = Direction::Up;
	}
	if (m_pathToCharacter.front().x> pos.first)
	{
		m_moveDirection = Direction::Right;
	}
	else if (m_pathToCharacter.front().x != pos.first)
	{
		m_moveDirection = Direction::Left;
	}
}
