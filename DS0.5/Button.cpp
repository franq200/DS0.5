#include "Button.h"

void Button::Init(const sf::Texture& texture, const sf::Vector2f& size, const sf::Vector2f& pos)
{
	setTexture(&texture);
	setSize(size);
	setPosition(pos);
}

bool Button::IsMouseInRange(const sf::RenderWindow& window)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f pos = getPosition();
	sf::Vector2f size = getSize();
	bool isIntXAxisRange = mousePos.x >= pos.x && mousePos.x <= pos.x + size.x;
	bool isInYAxisRange = mousePos.y >= pos.y && mousePos.y <= pos.y + size.y;
	return isIntXAxisRange && isInYAxisRange;
}
