#include "Warrior.h"
#include "Helper.h"

void Warrior::Init(const sf::Vector2f& spawnPos)
{
	setTexture(textures::warrior);
	setScale(0.33f, 0.33f);
	m_moveClock.restart();
	setPosition(spawnPos);
	m_hp = 100.f;
	m_hpBar.Init(getPosition(), m_hp);
}