#include "Character.h"
#include "Helper.h"

void Character::Init(sf::Vector2f spawnPos)
{
	setTexture(textures::character);
	setScale(0.25, 0.25);
	m_walkTextures = { textures::character, textures::walkCharacter1, textures::walkCharacter2, textures::walkCharacter3, textures::walkCharacter4 };
	setPosition(spawnPos);
	m_hpBar.Init(getPosition());
}

void Character::MakeMove(const sf::Vector2f& moveValue)
{
	WalkAnimation();
	move(moveValue);
	m_moveClock.restart();
}

void Character::LossHp()
{
	m_hp -= 10.f * character::damageTakenScaling;
}

void Character::GetHp()
{
	m_hp = 150.f;
	m_hpBar.Rescale(m_hp);
}

void Character::DrawHpBar(sf::RenderWindow& window)
{
	m_hpBar.Draw(window);
}

const int Character::GetMoveClockAsMilliseconds() const
{
	return m_moveClock.getElapsedTime().asMilliseconds();
}

const bool Character::IsDead() const
{
	return m_hp <= 0.f;
}

void Character::HpBarUpdate()
{
	m_hpBar.ChangeHpLevel(m_hp);
	if (getScale().x < 0)
	{
		sf::Vector2f pos = getPosition();
		m_hpBar.SetPosition({ pos.x - 50.f, pos.y });
		return;
	}
	m_hpBar.SetPosition(getPosition());
}

void Character::Restart(sf::Vector2f spawnPos)
{
	m_moveClock.restart();
	setPosition(spawnPos);
	m_hp = 100.f;
}

void Character::WalkAnimation()
{
	static int moveCounter = 0;
	setTexture(m_walkTextures[moveCounter]);
	if (moveCounter == 4)
	{
		setTexture(textures::walkCharacter4);
		moveCounter = 0;
		return;
	}
	moveCounter++;
}