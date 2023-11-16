#include "Warrior.h"
#include "Helper.h"
#include "Character.h"

Warrior::Warrior():
	Enemy(30.f, enemy::defaultWarriorHp, 0.33f, {textures::warrior})
{
}

void Warrior::Restart()
{
	setPosition(m_spawnPos);
	m_hpBar.Init(getPosition(), enemy::defaultWarriorHp);
}

void Warrior::Kill(Character& character)
{
	character::damageScaling = 1.3f;
	character.SetHp(130.f);
}
