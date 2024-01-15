#include "Moveable.h"
#include "Helper.h"

Moveable::Moveable(const std::vector<std::reference_wrapper<sf::Texture>>& walkTextures, float scale, int moveDistance) :
	m_walkTextures(walkTextures), m_scale(scale), m_moveDistance(moveDistance)
{
	m_movesToAnimate = static_cast<uint8_t>(10 / m_moveDistance);
}

sf::Vector2f Moveable::getPosition() const
{
	sf::Vector2f pos = sf::Sprite::getPosition();
	if (getScale().x < 0)
	{
		pos.x -= CalculateSize().x;
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
		move( -(CalculateSize().x), 0.f);
	}
	else if (moveValue.x < 0 && getScale().x > 0)
	{
		setScale(-m_scale, m_scale);
		move(CalculateSize().x, 0.f);
	}
}

void Moveable::Move(const sf::Vector2f& moveValue)
{
	m_movesCounter++;
	if (m_movesCounter >= m_movesToAnimate)
	{
		WalkAnimation();
		m_movesCounter = 0;
	}
	Rotate(moveValue);
	move(moveValue);
}

sf::Vector2f Moveable::CalculateSize() const
{
	return { getTexture()->getSize().x * m_scale, getTexture()->getSize().y * m_scale };
}

void Moveable::SetSpeed(int newSpeed)
{
	m_moveDistance = newSpeed;
	m_movesToAnimate = static_cast<uint8_t>(10 / m_moveDistance);
}
