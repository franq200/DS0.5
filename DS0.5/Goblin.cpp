#include "Goblin.h"
#include "Helper.h"
#include "Character.h"

Goblin::Goblin():
	Enemy(20.f, textures::goblin, enemy::defaultGoblinHp, 0.5f)
{
}

void Goblin::Restart()
{
	m_moveClock.restart();
	setPosition(m_spawnPos);
	m_hpBar.Init(getPosition(), enemy::defaultGoblinHp);
}

void Goblin::Kill(Character& character)
{
	character::damageTakenScaling = 0.8f;
	character.SetHp(120.f);
}
