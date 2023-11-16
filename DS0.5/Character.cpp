#include "Character.h"
#include "Helper.h"
#include "enemy.h"

Character::Character():
	Fightable(20.f, character::defaultHp), Moveable({ textures::character, textures::walkCharacter1, textures::walkCharacter2, textures::walkCharacter3, textures::walkCharacter4 }, character::defaultScale)
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
	setTexture(textures::character);
	setScale(character::defaultScale, character::defaultScale);
	setPosition(m_spawnPos);
	m_hpBar.Init(getPosition(), m_startHp);
}

void Character::MakeMove(const sf::Vector2f& moveValue)
{
	Moveable::Move(moveValue);
	UpdateHpBarPos();
}

void Character::Attack(Enemy& enemy)
{
	if (IsOpponentInRange(enemy.getPosition()))
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

sf::Vector2f Character::GetNextUp() const
{
	sf::Vector2f pos = getPosition();
	return { pos.x, pos.y - character::moveRange};
}

sf::Vector2f Character::GetNextDown() const
{
	sf::Vector2f pos = getPosition();
	return { pos.x, pos.y + character::moveRange };
}

sf::Vector2f Character::GetNextLeft() const
{
	sf::Vector2f pos = getPosition();
	return { pos.x - character::moveRange, pos.y};
}

sf::Vector2f Character::GetNextRight() const
{
	sf::Vector2f pos = getPosition();
	return { pos.x + character::moveRange, pos.y};
}

void Character::UpdateHpBarPos()
{
	m_hpBar.SetPosition(getPosition());
}

std::vector<sf::Vector2f> Character::GetEveryPossibleMovement() const
{
	return { GetNextRight(), GetNextLeft(), GetNextUp(), GetNextDown()};
}