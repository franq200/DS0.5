#include "enemy.h"
#include "Helper.h"
#include "Character.h"
#include "AStar.h"

Enemy::Enemy(float attackDamage, float startHp, float scale, const std::vector<std::reference_wrapper<sf::Texture>>& textures) :
	Fightable(attackDamage, startHp), Moveable(textures, scale)
{
}

void Enemy::Init(const sf::Vector2f& spawnPos)
{
	m_spawnPos = spawnPos;
	setTexture(m_walkTextures[0]);
	setScale(m_scale, m_scale);
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
	if (m_movesCounter == 0)
	{
		m_pathToCharacter = aStar::FindShortestPath(position::GetMapIndexesFromPosition(characterPos), position::GetMapIndexesFromPosition(getPosition()), map);
		if (!m_pathToCharacter.empty())
		{
			ChooseDirection();
			Enemy::Move();
			m_movesCounter++;
		}
	}
	else
	{
		if (m_movesCounter == 4)
		{
			Enemy::Move();
			m_movesCounter = 0;
		}
		else
		{
			Enemy::Move();
			m_movesCounter++;
		}
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
	case Direction::Right:
		Moveable::Move({ 10.f, 0.f });
		UpdateHpBarPos();
		break;
	case Direction::Left:
		Moveable::Move({ -10.f, 0.f });
		UpdateHpBarPos();
		break;
	case Direction::Down:
		Moveable::Move({ 0.f, 10.f });
		UpdateHpBarPos();
		break;
	case Direction::Up:
		Moveable::Move({ 0.f, -10.f });
		UpdateHpBarPos();
		break;
	}
}

void Enemy::ChooseDirection()
{
	IndexPosition pos = position::GetMapIndexesFromPosition(getPosition());
	if (m_pathToCharacter.back().y > pos.second)
	{
		m_moveDirection = Direction::Down;
	}
	else
	{
		m_moveDirection = Direction::Up;
	}
	if (m_pathToCharacter.back().x > pos.first)
	{
		m_moveDirection = Direction::Right;
	}
	else if (m_pathToCharacter.back().x != pos.first)
	{
		m_moveDirection = Direction::Left;
	}
}
