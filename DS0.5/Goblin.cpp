#include "Goblin.h"
#include "Helper.h"
#include "Character.h"

Goblin::Goblin():
	Enemy(20.f, enemy::defaultGoblinHp, 0.5f, {textures::goblin1, textures::goblin2, textures::goblin3, textures::goblin4, textures::goblin5})
{
}

void Goblin::Restart()
{
	setPosition(m_spawnPos);
	m_hpBar.Init(getPosition(), enemy::defaultGoblinHp);
}

void Goblin::Kill(Character& character)
{
	character::damageTakenScaling = 0.8f;
	character.SetHp(120.f);
}
