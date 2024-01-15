#include "Goblin.h"
#include "Helper.h"
#include "Character.h"

Goblin::Goblin():
	Enemy(Damage(20.f), Hp(100.f), 0.5f, AttackRange(45.f), AttackSpeed(700.f), {textures::goblin1, textures::goblin2, textures::goblin3, textures::goblin4, textures::goblin5})
{
}

void Goblin::Kill(Character& character)
{
	character::damageTakenScaling = 0.8f;
	character.SetHp(120.f);
}
