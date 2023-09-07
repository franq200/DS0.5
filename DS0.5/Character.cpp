#include "Character.h"
#include "Helper.h"

void Character::Init(sf::Vector2f spawnPos)
{
	setTexture(textures::character);
	setScale(0.25, 0.25);
	m_walkTextures = { textures::character, textures::walkCharacter1, textures::walkCharacter2, textures::walkCharacter3, textures::walkCharacter4 };
	setPosition(spawnPos);
	m_hpBar.Init(getPosition(), m_hp);
}

void Character::MakeMove(const sf::Vector2f& moveValue)
{
	WalkAnimation();
	move(moveValue);
	m_moveClock.restart();
}

bool Character::IsAttackSuccessful(const sf::Vector2f& enemyPos)
{
	if (m_attackClock.getElapsedTime().asMilliseconds() >= speed::characterAttackSpeed && sf::Mouse::isButtonPressed(sf::Mouse::Left) && IsEnemyInRange(enemyPos))
	{
		m_attackClock.restart();
		return true;
	}
	return false;
}

void Character::LossHp(float lostHp)
{
	if (m_hp <= 0)
	{
		throw std::exception("invalid hp state");
	}
	m_hp -= lostHp * character::damageTakenScaling;
}

void Character::SetHp(float newHp)
{
	m_hp = newHp;
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

void Character::Restart(const sf::Vector2f& spawnPos)
{
	m_moveClock.restart();
	setPosition(spawnPos);
	m_hp = 100.f;
}

bool Character::IsEnemyInRange(const sf::Vector2f& enemyPos) const
{
	sf::Vector2f pos = getPosition();
	return (std::abs(pos.x - enemyPos.x) <= 60 && std::abs(pos.y - enemyPos.y) <= 60);
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