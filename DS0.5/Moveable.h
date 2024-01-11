#pragma once
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
	Moveable(const std::vector<std::reference_wrapper<sf::Texture>>& walkTextures, float scale, float moveDistance);
	sf::Vector2f getPosition() const;
protected:
	void WalkAnimation();
	void Rotate(const sf::Vector2f& moveValue);
	void Move(const sf::Vector2f& moveValue);
	void SetSpeed(float speedPercent);
	const std::vector<std::reference_wrapper<sf::Texture>> m_walkTextures;
	const float m_scale;
	float m_moveDistance = 0.f;
	int m_movesCounter = 0;
	sf::Vector2f m_size;
private:
	int m_animationCounter = 0;
	uint8_t m_movesToAnimate = 0;
};

