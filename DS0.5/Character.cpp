#include "Character.h"
#include "Helper.h"

sf::Vector2f Character::getPosition() const
{
	sf::Vector2f pos = sf::Sprite::getPosition();
	if (getScale().x < 0)
	{
		pos.x -= 50.f;
	}
	return pos;
}

void Character::Init(sf::Vector2f spawnPos)
{
	setTexture(textures::character);
	setScale(character::defaultScale, character::defaultScale);
	m_walkTextures = { textures::character, textures::walkCharacter1, textures::walkCharacter2, textures::walkCharacter3, textures::walkCharacter4 };
	setPosition(spawnPos);
	m_hpBar.Init(getPosition(), character::defaultHp);
}

void Character::MakeMove(const sf::Vector2f& moveValue)
{
	WalkAnimation();
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
	move(moveValue);
	UpdateHpBarPos();
	m_moveClock.restart();
}

bool Character::IsAttackSuccessful(const sf::Vector2f& opponentPos)
{
	if (m_attackClock.getElapsedTime().asMilliseconds() >= speed::characterAttackSpeed && sf::Mouse::isButtonPressed(sf::Mouse::Left) && IsOpponentInRange(opponentPos))
	{
		m_attackClock.restart();
		return true;
	}
	return false;
}

int Character::GetMoveClockAsMilliseconds() const
{
	return m_moveClock.getElapsedTime().asMilliseconds();
}

void Character::Restart(const sf::Vector2f& spawnPos)
{
	m_moveClock.restart();
	setPosition(spawnPos);
	m_hpBar.SetHp(character::defaultHp);
}

sf::Vector2f Character::GetNextUp() const
{
	sf::Vector2f pos = getPosition();
	return { pos.x, pos.y - character::moveRange};
}

sf::Vector2f Character::GetNextDown() const
{
	sf::Vector2f pos = getPosition();
	return { pos.x, pos.y + size::cellSize + character::moveRange };
}

sf::Vector2f Character::GetNextLeft() const
{
	sf::Vector2f pos = getPosition();
	return { pos.x - character::moveRange, pos.y};
}

sf::Vector2f Character::GetNextRight() const
{
	sf::Vector2f pos = getPosition();
	return { pos.x + size::cellSize + character::moveRange, pos.y};
}

void Character::UpdateHpBarPos()
{
	m_hpBar.SetPosition(getPosition());
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