#include "Dragon.h"
#include "Helper.h"
#include "Character.h"

Dragon::Dragon():
	Enemy(60.f, 250.f, 0.2f, { textures::dragon })
{
	m_size = { 100.f, 60.f };
}

void Dragon::Kill(Character& character)
{
	character.SetHp(150.f);
}
