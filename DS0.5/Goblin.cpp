#include "Goblin.h"
#include "Helper.h"

void Goblin::Init(const sf::Vector2f& spawnPos)
{
	setTexture(textures::goblin);
	setScale(0.5, 0.5);
	m_moveClock.restart();
	setPosition(spawnPos);
	m_hpBar.Init(getPosition());
	m_hp = 100.f;
}
