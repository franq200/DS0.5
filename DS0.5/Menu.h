#pragma once
#include "Button.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Menu
{
public:
	void Init();
	void Update(const sf::RenderWindow& window);
	bool ShouldExit(const sf::RenderWindow& window);
	bool ShouldStart(const sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);
private:
	std::vector<Button> m_buttons;
};

