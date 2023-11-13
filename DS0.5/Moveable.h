#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class Moveable : public virtual sf::Sprite
{
public:
	Moveable(std::vector<sf::Texture> walkTextures, float scale);
	void Init(std::vector<sf::Texture> walkTextures);
	sf::Vector2f getPosition() const;
protected:
	void WalkAnimation();
	void Rotate(const sf::Vector2f& moveValue);
	void Move(const sf::Vector2f& moveValue);
	std::vector<sf::Texture> m_walkTextures;
	const float m_scale;
	sf::Clock m_moveClock;
	int m_movesCounter = 0;
private:
	int m_animationCounter = 0;
};

