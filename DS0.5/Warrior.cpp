#include "Warrior.h"
#include "Helper.h"
#include "Character.h"

Warrior::Warrior():
	Enemy(30.f, textures::warrior, enemy::defaultWarriorHp, 0.33f)
{
}

void Warrior::Restart()
{
	m_moveClock.restart();
	setPosition(m_spawnPos);
	m_hpBar.Init(getPosition(), enemy::defaultWarriorHp);
	m_movesCounter = 0;
}

void Warrior::Kill(Character& character)
{
	character::damageScaling = 1.3f;
	character.SetHp(130.f);
}
