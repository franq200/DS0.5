#include "Dragon.h"
#include "Helper.h"
#include "Character.h"

Dragon::Dragon():
	Enemy(Damage(60.f), Hp(250.f), 0.2f, AttackRange(90.f), AttackSpeed(700.f), { textures::dragon })
{
}

void Dragon::Kill(Character& character)
{
	character.SetHp(150.f);
}
