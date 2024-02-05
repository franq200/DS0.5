#include "enemy.h"
#include "Helper.h"
#include "Character.h"
#include "AStar.h"
#include "IClock.h"
#include "ICharacter.h"
#include "HpBar.h"

Enemy::Enemy(Damage attackDamage, Hp startHp, float scale, AttackRange attackRange, AttackSpeed attackSpeed, const std::vector<std::reference_wrapper<sf::Texture>>& textures, std::unique_ptr<IHpBar> hpBar, std::unique_ptr<IClock> clock) :
	Fightable(attackDamage, startHp, attackRange, attackSpeed, std::move(hpBar), std::move(clock)), Moveable(textures, scale, 2)
{
}

void Enemy::Init(const sf::Vector2f& spawnPos)
{
	m_spawnPos = spawnPos;
	setTexture(m_walkTextures[0]);
	setScale(m_scale, m_scale);
	setPosition(m_spawnPos);
	m_hpBar->Init(getPosition(), m_startHp, CalculateSize());
}

void Enemy::Restart()
{
	setPosition(m_spawnPos);
	m_hpBar->Restart(getPosition(), m_startHp);
}

void Enemy::TryKill(ICharacter& character)
{
	if (IsDead())
	{
		Kill(character);
	}
}

void Enemy::Attack(ICharacter& character)
{
	if (IsOpponentInRange(character.Moveable::getPosition(), Moveable::getPosition()))
	{
		if (!m_isAttackClockRestarted)
		{
			m_attackClock->RestartClock();
			m_isAttackClockRestarted = true;
		}
		else if (static_cast<AttackSpeed>(m_attackClock->GetElapsedTimeAsMilliseconds()) >= m_attackSpeed)
		{
			m_attackClock->RestartClock();
			character.LossHp(m_attackDamage * character.GetDamageTakenScaling());
		}
	}
	else if (m_isAttackClockRestarted)
	{
		m_isAttackClockRestarted = false;
	}
}

void Enemy::PreparePathAndMove(const sf::Vector2f& characterPos, const std::vector<std::vector<bool>>& map)
{
	if (m_movesCounter == 0 )
	{
		m_pathToCharacter = aStar::FindShortestPath(position::GetMapIndexesFromPosition(characterPos), position::GetMapIndexesFromPosition(getPosition()), map);
		if (!m_pathToCharacter.empty())
		{
			ChooseDirection();
			Enemy::Move();
		}
	}
	else
	{
		Enemy::Move();
	}
}

void Enemy::UpdateHpBarPos()
{
	m_hpBar->SetPosition(Moveable::getPosition());
}

void Enemy::Move()
{
	switch (m_moveDirection)
	{
	case Direction::Right:
		Moveable::Move({ static_cast<float>(m_moveDistance), 0.f });
		break;
	case Direction::Left:
		Moveable::Move({ static_cast<float>(m_moveDistance) *(-1), 0.f});
		break;
	case Direction::Down:
		Moveable::Move({ 0.f, static_cast<float>(m_moveDistance) });
		break;
	case Direction::Up:
		Moveable::Move({ 0.f, static_cast<float>(m_moveDistance) * (-1) });
		break;
	}
	UpdateHpBarPos();
}

void Enemy::ChooseDirection()
{
	IndexPosition pos = position::GetMapIndexesFromPosition(Moveable::getPosition());
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
