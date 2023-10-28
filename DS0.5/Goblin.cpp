#include "Goblin.h"
#include "Helper.h"
#include "Character.h"

void Goblin::Init(const sf::Vector2f& spawnPos)
{
	m_spawnPos = spawnPos;
	setTexture(textures::goblin);
	setScale(0.5, 0.5);
	m_moveClock.restart();
	setPosition(spawnPos);
	m_hpBar.Init(getPosition(), enemy::defaultGoblinHp);
	m_attackDamage = 20.f;
}

void Goblin::Restart()
{
	m_moveClock.restart();
	setPosition(m_spawnPos);
	m_hpBar.Init(getPosition(), enemy::defaultGoblinHp);
	m_movesCounter = 0;
}

void Goblin::Kill(Character& character)
{
	character::damageTakenScaling = 0.8f;
	character.SetHp(120.f);
}
