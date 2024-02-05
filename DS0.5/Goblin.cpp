#include "Goblin.h"
#include "Helper.h"
#include "Character.h"
#include "ICharacter.h"
#include "IClock.h"
#include "HpBar.h"

Goblin::Goblin(std::unique_ptr<IHpBar> hpBar, std::unique_ptr<IClock> clock):
	Enemy(Damage(20.f), Hp(100.f), 0.5f, AttackRange(45.f), AttackSpeed(700.f), {textures::goblin1, textures::goblin2, textures::goblin3, textures::goblin4, textures::goblin5}, std::move(hpBar), std::move(clock))
{
}

void Goblin::Kill(ICharacter& character)
{
	character.SetDamegeTakenScaling(DamageScale(0.8f));
	character.SetHp(120.f);
}
