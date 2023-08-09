#pragma once
#include <SFML/Graphics.hpp>

class Fightable
{
public:
	virtual void Attack() = 0;
protected:
	//virtual void AttackAnimation() = 0;
	std::vector<sf::Texture> m_attackTextures;
};

