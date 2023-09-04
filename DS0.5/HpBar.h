#pragma once
#include <SFML/Graphics.hpp>

class HpBar
{
public:
	void Init(const sf::Vector2f& goblinPos, const float& hp);
	void SetPosition(const sf::Vector2f& goblinPos);
	void ChangeHpLevel(const float& hp);
	void Rescale(const float& hp);
	void Draw(sf::RenderWindow& window);
private:
	sf::RectangleShape m_hpBarBackground;
	sf::RectangleShape m_hpBar;
};

