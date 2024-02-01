#include "Warrior.h"
#include "Helper.h"
#include "Character.h"

Warrior::Warrior(std::unique_ptr<IHpBar> hpBar):
	Enemy(Damage(30.f), Hp(110.f), 0.33f, AttackRange(50.f), AttackSpeed(700.f), {textures::warrior}, std::move(hpBar))
{
}

void Warrior::Kill(Character& character)
{
	character.SetDamegeGivenScaling(1.3f);
	character.SetHp(130.f);
}
