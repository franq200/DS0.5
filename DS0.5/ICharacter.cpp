#include "ICharacter.h"
#include "Helper.h"

ICharacter::ICharacter(std::unique_ptr<IHpBar> hpBar, std::unique_ptr<IClock> clock):
	Fightable(Damage(20.f), Hp(100.f), AttackRange(55.f), AttackSpeed(300.f), std::move(hpBar), std::move(clock)),
	Moveable({ textures::character, textures::walkCharacter1, textures::walkCharacter2, textures::walkCharacter3, textures::walkCharacter4 }, 0.25f, 3)
{
}
