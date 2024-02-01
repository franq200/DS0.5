#pragma once
#include <SFML/Graphics.hpp>

class Button : public sf::RectangleShape
{
public:
	void Init(const sf::Texture& texture, const sf::Vector2f& size, const sf::Vector2f& pos);
	bool IsMouseInRange(const sf::RenderWindow& window);
};