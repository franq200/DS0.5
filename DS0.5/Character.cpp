#include "Character.h"
#include "Helper.h"
#include "enemy.h"
#include "Map.h"

Character::Character():
	Fightable(Damage(20.f), Hp(100.f), AttackRange(55.f), AttackSpeed(300.f)), 
	Moveable({ textures::character, textures::walkCharacter1, textures::walkCharacter2, textures::walkCharacter3, textures::walkCharacter4 }, 0.25f, 3)
{
}

void Character::Teleport(const sf::Vector2f& newPosition)
{
	setPosition(newPosition);
	m_hpBar.SetPosition(getPosition());
}

bool Character::IsAbleToAttack()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_isAbleToAttack)
	{
		return true;
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_isAbleToAttack)
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
	m_hpBar.Init(getPosition(), m_startHp, CalculateSize());
}

void Character::MakeMove(const sf::Vector2f& moveValue)
{
	Moveable::Move(moveValue);
	UpdateHpBarPos();
}

void Character::Attack(Enemy& enemy)
{
	if (IsOpponentInRange(enemy.Moveable::getPosition(), Moveable::getPosition()))
	{
		m_isAbleToAttack = false;
		enemy.LossHp(m_attackDamage);
		enemy.TryKill(*this);
	}
}

void Character::Restart()
{
	setScale(character::defaultScale, character::defaultScale);
	setPosition(m_spawnPos);
	m_hpBar.SetHp(character::defaultHp);
	m_hpBar.SetPosition(getPosition());
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
	sf::Vector2f pos = getPosition();
	return { pos.x, pos.y - m_moveDistance};
}

sf::Vector2f Character::GetNextDown() const
{
	sf::Vector2f pos = getPosition();
	return { pos.x, pos.y + m_moveDistance };
}

sf::Vector2f Character::GetNextLeft() const
{
	sf::Vector2f pos = getPosition();
	return { pos.x - m_moveDistance, pos.y};
}

sf::Vector2f Character::GetNextRight() const
{
	sf::Vector2f pos = getPosition();
	return { pos.x + m_moveDistance, pos.y};
}

void Character::UpdateHpBarPos()
{
	m_hpBar.SetPosition(getPosition());
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
