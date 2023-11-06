#include "Dragon.h"
#include "Helper.h"
#include "Character.h"

Dragon::Dragon():
	Enemy(60.f, textures::dragon, enemy::defaultDragonHp, 0.2f)
{
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
