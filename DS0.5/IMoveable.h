#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class IMoveable : public virtual sf::Sprite
{
public:
	virtual sf::Vector2f getPosition() const = 0;
	virtual void SetSpeed(int newSpeed) = 0;
};

