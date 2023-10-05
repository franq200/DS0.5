#include "Warrior.h"
#include "Helper.h"
#include "Character.h"

void Warrior::Init(const sf::Vector2f& spawnPos)
{
	m_spawnPos = spawnPos;
	setTexture(textures::warrior);
	setScale(0.33f, 0.33f);
	m_moveClock.restart();
	setPosition(spawnPos);
	m_hpBar.Init(getPosition(), enemy::defaultWarriorHp);
	m_attackDamage = 30.f;
}

void Warrior::Restart()
{
	m_moveClock.restart();
	setPosition(m_spawnPos);
	m_hpBar.IncreaseMaxHp(enemy::defaultWarriorHp);
	m_movesCounter = 0;
}

void Warrior::Kill(Character& character)
{
	character::damageScaling = 1.3f;
	character.SetHp(130.f);
}
