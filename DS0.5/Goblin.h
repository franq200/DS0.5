#pragma once
#include "enemy.h"
#include <SFML/Graphics.hpp>

class IClock;
class ICharacter;

class Goblin : public Enemy
{
public:
	Goblin(std::unique_ptr<IHpBar> hpBar, std::unique_ptr<IClock> clock);
private:
	void Kill(ICharacter& character) override;
};