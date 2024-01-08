#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class Moveable : public virtual sf::Sprite
{
public:
	Moveable(const std::vector<std::reference_wrapper<sf::Texture>>& walkTextures, float scale);
	sf::Vector2f getPosition() const;
protected:
	void WalkAnimation();
	void Rotate(const sf::Vector2f& moveValue);
	void Move(const sf::Vector2f& moveValue);
	const std::vector<std::reference_wrapper<sf::Texture>> m_walkTextures;
	const float m_scale;
	int m_movesCounter = 0;
	sf::Vector2f m_size;
private:
	int m_animationCounter = 0;
};

