#include "Character.h"
#include "Helper.h"

void Character::Init(sf::Vector2f spawnPos)
{
	setTexture(textures::character);
	setScale(0.25, 0.25);
	m_walkTextures = { textures::character, textures::walkCharacter1, textures::walkCharacter2, textures::walkCharacter3, textures::walkCharacter4 };
	setPosition(spawnPos);
}

void Character::MakeMove(const sf::Vector2f& moveValue)
{
	WalkAnimation();
	move(moveValue);
	m_moveClock.restart();
}

void Character::Attack()
{
	//AttackAnimation();

}

int Character::GetElapsedTimeAsMilliseconds() const
{
	return m_moveClock.getElapsedTime().asMilliseconds();
}

void Character::WalkAnimation()
{
	static int moveCounter = 0;
	setTexture(m_walkTextures[moveCounter]);
	if (moveCounter == 4)
	{
		setTexture(textures::walkCharacter4);
		moveCounter = 0;
		return;
	}
	moveCounter++;
}

/*
void Character::AttackAnimation()
{
	static int attackCounter = 0;
	setTexture(m_attackTextures[attackCounter]);
	if (attackCounter == 4)
	{
		setTexture(textures::walkCharacter4);
		attackCounter = 0;
		return;
	}
	attackCounter++;
}
*/
