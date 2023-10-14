#include "Character.h"
#include "Helper.h"
#include "enemy.h"

void Character::Teleport(const sf::Vector2f& newPosition)
{
	setPosition(newPosition);
	m_hpBar.SetPosition(getPosition());
}

sf::Vector2f Character::getPosition() const
{
	sf::Vector2f pos = sf::Sprite::getPosition();
	if (getScale().x < 0)
	{
		pos.x -= 50.f;
	}
	return pos;
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
	m_walkTextures = { textures::character, textures::walkCharacter1, textures::walkCharacter2, textures::walkCharacter3, textures::walkCharacter4 };
	setPosition(m_spawnPos);
	m_hpBar.Init(getPosition(), character::defaultHp);
	m_attackDamage = 20.f;
}

void Character::MakeMove(const sf::Vector2f& moveValue)
{
	WalkAnimation();
	Rotate(moveValue);
	move(moveValue);
	UpdateHpBarPos();
	m_moveClock.restart();
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

int Character::GetMoveClockAsMilliseconds() const
{
	return m_moveClock.getElapsedTime().asMilliseconds();
}

void Character::Restart()
{
	m_moveClock.restart();
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

void Character::Rotate(const sf::Vector2f& moveValue)
{
	if (moveValue.x != 0)
	{
		if (moveValue.x == 10 && getScale().x < 0)
		{
			setScale(character::defaultScale, character::defaultScale);
			move(-size::cellSize, 0.f);
		}
		else if (moveValue.x == -10 && getScale().x > 0)
		{
			setScale(-character::defaultScale, character::defaultScale);
			move(size::cellSize, 0.f);
		}
	}
}

void Character::WalkAnimation()
{
	setTexture(m_walkTextures[m_moveCounter]);
	if (m_moveCounter == m_walkTextures.size() - 1)
	{
		setTexture(textures::walkCharacter4);
		m_moveCounter = 0;
		return;
	}
	m_moveCounter++;
}