#include "Dragon.h"
#include "Helper.h"
#include "Character.h"

void Dragon::Init(const sf::Vector2f& spawnPos)
{
	m_spawnPos = spawnPos;
	setTexture(textures::dragon);
	setScale(0.2f, 0.2f);
	m_moveClock.restart();
	setPosition(spawnPos);
	m_attackDamage = 60.f;
}

void Dragon::Restart()
{
	m_moveClock.restart();
	setPosition(m_spawnPos);
	m_hpBar.Init(getPosition(), enemy::defaultDragonHp);
	m_movesCounter = 0;
}

void Dragon::Kill(Character& character)
{
	character.SetHp(150.f);
}
