#include "Moveable.h"

Moveable::Moveable(std::vector<sf::Texture> walkTextures):
	m_walkTextures(walkTextures)
{
}

void Moveable::Init(std::vector<sf::Texture> walkTextures)
{
	m_walkTextures = walkTextures;
}

void Moveable::WalkAnimation()
{
	setTexture(m_walkTextures[m_moveCounter]);
	if (m_moveCounter == m_walkTextures.size() - 1)
	{
		setTexture(m_walkTextures.back());
		m_moveCounter = 0;
		return;
	}
	m_moveCounter++;
}
