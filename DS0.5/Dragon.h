#pragma once
#include "enemy.h"
#include <SFML/Graphics.hpp>

class IClock;
class ICharacter;

class Dragon : public Enemy
{
public:
	Dragon(std::unique_ptr<IHpBar> hpBar, std::unique_ptr<IClock> clock);
private:
	void Kill(ICharacter& character) override;
};

