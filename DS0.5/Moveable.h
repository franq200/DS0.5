#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class Moveable : public virtual sf::Sprite
{
public:
	Moveable(std::vector<sf::Texture> walkTextures);
	void Init(std::vector<sf::Texture> walkTextures);
protected:
	void WalkAnimation();
private:
	int m_moveCounter = 0;
	std::vector<sf::Texture> m_walkTextures;
};

