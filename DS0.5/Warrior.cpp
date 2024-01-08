#include "Warrior.h"
#include "Helper.h"
#include "Character.h"

Warrior::Warrior():
	Enemy(30.f, 110.f, 0.33f, {textures::warrior})
{
	m_size = { 50.f, 50.f };
}

void Warrior::Kill(Character& character)
{
	character::damageScaling = 1.3f;
	character.SetHp(130.f);
}
