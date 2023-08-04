#include "Character.h"
#include "Helper.h"

void Character::Init(sf::Vector2f pos)
{
	setTexture(&textures::character);
	setSize({ 50.f, 50.f });
	setPosition(pos);
}
