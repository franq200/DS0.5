#pragma once
#include <SFML/Graphics.hpp>

class MiniMap
{
public:
	void Init();
	void Update(const sf::Vector2f& characterPos);
	void Draw(sf::RenderWindow& window);
	void DrawView(sf::RenderWindow& window);
	void DrawOutline(sf::RenderWindow& window);
private:
	sf::View m_miniMap;
	sf::RectangleShape m_outline;
};

