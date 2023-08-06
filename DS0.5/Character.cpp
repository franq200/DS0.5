#include "Character.h"
#include "Helper.h"

void Character::Init(sf::Vector2f pos)
{
	setTexture(textures::character);
	setScale(0.25, 0.25);
}

void Character::MoveCharacter(const sf::Vector2f& moveValue, sf::Clock& moveClock)
{
	static int moveCounter = 0;
	if (moveCounter == 0)
	{
		setTexture(textures::character);
		moveCounter++;
	}
	if (moveCounter == 1)
	{
		setTexture(textures::walkCharacter1);
		moveCounter++;
	}
	else if (moveCounter == 2)
	{
		setTexture(textures::walkCharacter2);
		moveCounter++;
	}
	else if (moveCounter == 3)
	{
		setTexture(textures::walkCharacter3);
		moveCounter++;
	}
	else if (moveCounter == 4)
	{
		setTexture(textures::walkCharacter4);
		moveCounter = 0;
	}
	move(moveValue);
	moveClock.restart();
}
