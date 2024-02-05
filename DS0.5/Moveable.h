#pragma once
//#include "IMoveable.h"
#include <vector>
#include <SFML/Graphics.hpp>

enum class Direction
{
	Left = 0,
	Right,
	Down,
	Up
};

class Moveable : public virtual sf::Sprite
{
public:
	Moveable(const std::vector<std::reference_wrapper<sf::Texture>>& walkTextures, float scale, int moveDistance);
	sf::Vector2f getPosition() const;
	void SetSpeed(int newSpeed);
protected:
	void WalkAnimation();
	void Rotate(const sf::Vector2f& moveValue);
	void Move(const sf::Vector2f& moveValue);
	sf::Vector2f CalculateSize() const;
	const std::vector<std::reference_wrapper<sf::Texture>> m_walkTextures;
	const float m_scale;
	int m_moveDistance = 0;
	int m_movesCounter = 0;
private:
	int m_animationCounter = 0;
	uint8_t m_movesToAnimate = 0;
};

