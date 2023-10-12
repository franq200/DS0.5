#include "MiniMap.h"
#include "Helper.h"

void MiniMap::Init()
{
	m_miniMap.setViewport(sf::FloatRect(0.75f, 0.f, 0.25f, 0.5f));
	m_outline.setSize({ size::windowSizeX * 0.25f + 10.f, size::windowSizeY * 0.25f + 10.f });
	m_outline.setOutlineThickness(2.f);
	m_outline.setOutlineColor(sf::Color::Yellow);
	m_outline.setPosition(0.75f * size::windowSizeX, 0.f);
	m_outline.setFillColor(sf::Color(0, 0, 0, 255));
}

void MiniMap::Update(const sf::Vector2f& characterPos)
{
	m_miniMap.setCenter(characterPos.x + size::cellSize, characterPos.y + size::cellSize / 2);
}

void MiniMap::Draw(sf::RenderWindow& window)
{
	window.setView(m_miniMap);
	window.draw(m_outline);
}
