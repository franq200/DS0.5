#pragma once
#include <SFML/Graphics.hpp>

class Moveable : public sf::Sprite
{
public:
	void MakeMove(const sf::Vector2f& moveValue, sf::Clock& moveClock);
	void Animate(sf::Clock& moveClock);
};

