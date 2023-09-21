#include "Dragon.h"
#include "Helper.h"

void Dragon::Init(const sf::Vector2f& spawnPos)
{
	setTexture(textures::dragon);
	setScale(0.2f, 0.2f);
	m_moveClock.restart();
	setPosition(spawnPos);
	m_hpBar.Init(getPosition(), 250.f);
	m_attackDamage = 60.f;
}
