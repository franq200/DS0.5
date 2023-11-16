#include "Dragon.h"
#include "Helper.h"
#include "Character.h"

Dragon::Dragon():
	Enemy(60.f, enemy::defaultDragonHp, 0.2f, { textures::dragon })
{
}

void Dragon::Restart()
{
	setPosition(m_spawnPos);
	m_hpBar.Init(getPosition(), enemy::defaultDragonHp);
}

void Dragon::Kill(Character& character)
{
	character.SetHp(150.f);
}
