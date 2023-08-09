#pragma once
#include <SFML/Graphics.hpp>

class Moveable
{
public:
	//virtual void MakeMove(const sf::Vector2f& moveValue) = 0;
protected:
	//virtual void WalkAnimation(sf::Clock& moveClock);
	std::vector<sf::Texture> m_walkTextures;
};

