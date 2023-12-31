#include "Moveable.h"
#include "Helper.h"

Moveable::Moveable(const std::vector<std::reference_wrapper<sf::Texture>>& walkTextures, float scale) :
	m_walkTextures(walkTextures), m_scale(scale)
{
}

sf::Vector2f Moveable::getPosition() const
{
	sf::Vector2f pos = sf::Sprite::getPosition();
	if (getScale().x < 0)
	{
		pos.x -= 50.f;
	}
	return pos;
}

void Moveable::WalkAnimation()
{
	setTexture(m_walkTextures[m_animationCounter]);
	if (m_animationCounter == m_walkTextures.size() - 1)
	{
		m_animationCounter = 0;
		return;
	}
	m_animationCounter++;
}

void Moveable::Rotate(const sf::Vector2f& moveValue)
{
	if (moveValue.x > 0 && getScale().x < 0)
	{
		setScale(m_scale, m_scale);
		move(-m_size.x , 0.f);
	}
	else if (moveValue.x < 0 && getScale().x > 0)
	{
		setScale(-m_scale, m_scale);
		move(m_size.x, 0.f);
	}
}

void Moveable::Move(const sf::Vector2f& moveValue)
{
	WalkAnimation();
	Rotate(moveValue);
	move(moveValue);
}
