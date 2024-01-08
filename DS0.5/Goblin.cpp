#include "Goblin.h"
#include "Helper.h"
#include "Character.h"

Goblin::Goblin():
	Enemy(20.f, 100.f, 0.5f, {textures::goblin1, textures::goblin2, textures::goblin3, textures::goblin4, textures::goblin5})
{
	m_size = { 35.f, 50.f };
}

void Goblin::Kill(Character& character)
{
	character::damageTakenScaling = 0.8f;
	character.SetHp(120.f);
}
