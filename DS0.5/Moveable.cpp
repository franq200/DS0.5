#include "Moveable.h"
#include "Helper.h"

void Moveable::MakeMove(const sf::Vector2f & moveValue, sf::Clock & moveClock)
{
	Animate(moveClock);
	move(moveValue);
	moveClock.restart();
}

void Moveable::Animate(sf::Clock& moveClock)
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
}
