#pragma once
#include <SFML/Graphics.hpp>

class Character : public sf::Sprite
{
public:
	void Init(sf::Vector2f pos);
	void MoveCharacter(const sf::Vector2f& moveValue, sf::Clock& moveClock);
private:
};

