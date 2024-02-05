#include "Dragon.h"
#include "Helper.h"
#include "Character.h"
#include "ICharacter.h"
#include "IClock.h"
#include "HpBar.h"

Dragon::Dragon(std::unique_ptr<IHpBar> hpBar, std::unique_ptr<IClock> clock):
	Enemy(Damage(60.f), Hp(250.f), 0.2f, AttackRange(90.f), AttackSpeed(700.f), { textures::dragon }, std::move(hpBar), std::move(clock))
{
}

void Dragon::Kill(ICharacter& character)
{
	character.SetHp(150.f);
}
