#include "Character.h"
#include "Helper.h"
#include "enemy.h"
#include "Map.h"
#include "IClock.h"
#include "HpBar.h"

Character::Character(std::unique_ptr<IHpBar> hpBar, std::unique_ptr<IMouse> mouse, std::unique_ptr<IClock> clock) :
	ICharacter(std::move(hpBar),std::move(clock)),
	m_mouse(std::move(mouse))
{
}

void Character::Teleport(const sf::Vector2f& newPosition)
{
	setPosition(newPosition);
	m_hpBar->SetPosition(GetPositionWithRotate());
}

bool Character::IsAbleToAttack()
{
	const bool isClickedAttack = m_mouse->IsLeftButtonPressed();
	if (isClickedAttack && m_isAbleToAttack)
	{
		return true;
	}
	else if (!isClickedAttack && !m_isAbleToAttack)
	{
		m_isAbleToAttack = true;
		return false;
	}
	return false;
}

void Character::Init(sf::Vector2f spawnPos)
{
	m_spawnPos = spawnPos;
	setScale(m_scale, m_scale);
	setTexture(textures::character);
	setPosition(m_spawnPos);
	m_hpBar->Init(GetPositionWithRotate(), m_startHp, CalculateSize(), HpBarPosition::LeftTopCorner);
}

void Character::MakeMove(const sf::Vector2f& moveValue)
{
	Moveable::Move(moveValue);
	UpdateHpBarPos();
}

void Character::Attack(Enemy& enemy)
{
	if (IsOpponentInRange(enemy.Moveable::GetPositionWithRotate(), Moveable::GetPositionWithRotate()))
	{
		m_isAbleToAttack = false;
		enemy.LossHp(m_attackDamage);
		enemy.TryKill(*this);
	}
}

void Character::Restart()
{
	setScale(m_scale, m_scale);
	setPosition(m_spawnPos);
	m_hpBar->SetNewMaxHp(m_startHp);
	m_hpBar->SetPosition(GetPositionWithRotate());
}

bool Character::IsRightMovePossible(const Map* map) const
{
	return !map->GetCollisionSquare(GetNextRight(), { CellState::Filled, CellState::CloseGate });
}

bool Character::IsUpMovePossible(const Map* map) const
{
	return !map->GetCollisionSquare(GetNextUp(), { CellState::Filled, CellState::CloseGate });
}

bool Character::IsDownMovePossible(const Map* map) const
{
	return !map->GetCollisionSquare(GetNextDown(), { CellState::Filled, CellState::CloseGate });
}

bool Character::IsLeftMovePossible(const Map* map) const
{
	return !map->GetCollisionSquare(GetNextLeft(), { CellState::Filled, CellState::CloseGate });
}

sf::Vector2f Character::GetNextUp() const
{
	sf::Vector2f pos = GetPositionWithRotate();
	return { pos.x, pos.y - m_moveDistance};
}

sf::Vector2f Character::GetNextDown() const
{
	sf::Vector2f pos = GetPositionWithRotate();
	return { pos.x, pos.y + m_moveDistance };
}

sf::Vector2f Character::GetNextLeft() const
{
	sf::Vector2f pos = GetPositionWithRotate();
	return { pos.x - m_moveDistance, pos.y};
}

sf::Vector2f Character::GetNextRight() const
{
	sf::Vector2f pos = GetPositionWithRotate();
	return { pos.x + m_moveDistance, pos.y};
}

void Character::UpdateHpBarPos()
{
	m_hpBar->SetPosition(GetPositionWithRotate());
}

std::vector<sf::Vector2f> Character::GetEveryPossibleMovement() const
{
	return { GetNextRight(), GetNextLeft(), GetNextUp(), GetNextDown()};
}

bool Character::IsSlowed()
{
	return m_moveDistance < 3;
}

int Character::GetMoveDistance() const
{
	return m_moveDistance;
}
