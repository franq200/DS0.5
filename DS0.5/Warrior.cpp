#include "Warrior.h"
#include "Helper.h"
#include "Character.h"

Warrior::Warrior():
	Enemy(Damage(30.f), Hp(110.f), 0.33f, AttackRange(50.f), AttackSpeed(700.f), {textures::warrior})
{
}

void Warrior::Kill(Character& character)
{
	character::damageScaling = 1.3f;
	character.SetHp(130.f);
}
