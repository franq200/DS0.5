#include "Warrior.h"
#include "Helper.h"
#include "Character.h"
#include "ICharacter.h"
#include "IClock.h"
#include "HpBar.h"

Warrior::Warrior(std::unique_ptr<IHpBar> hpBar, std::unique_ptr<IClock> clock):
	Enemy(Damage(30.f), Hp(110.f), 0.33f, AttackRange(50.f), AttackSpeed(700.f), {textures::warrior}, std::move(hpBar), std::move(clock))
{
}

void Warrior::Kill(ICharacter& character)
{
	character.SetDamageGivenScaling(1.3f);
	character.SetHp(130.f);
}
