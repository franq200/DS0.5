#include "Menu.h"
#include "Helper.h"

void Menu::Init()
{
	m_buttons.resize(2);
	sf::Vector2f buttonSize{ 337.f, 149.f };
	m_buttons[0].Init(textures::start, buttonSize, { size::windowSizeX / 2 - buttonSize.x / 2, size::windowSizeY / 2 - buttonSize.y - 10.f });
	m_buttons[0].setOutlineColor(sf::Color::Yellow);
	m_buttons[1].Init(textures::exit, buttonSize, {size::windowSizeX / 2 - buttonSize.x / 2, size::windowSizeY / 2 + 10.f});
	m_buttons[1].setOutlineColor(sf::Color::Yellow);
}

void Menu::Update(const sf::RenderWindow& window)
{
	for (auto& el : m_buttons)
	{
		el.IsMouseInRange(window) ? el.setOutlineThickness(3.f) : el.setOutlineThickness(0.f);
	}
}

bool Menu::ShouldExit(const sf::RenderWindow& window)
{
	return m_buttons[1].IsMouseInRange(window);
}

bool Menu::ShouldStart(const sf::RenderWindow& window)
{
	return m_buttons[0].IsMouseInRange(window);
}

void Menu::Draw(sf::RenderWindow& window)
{
	for (auto el : m_buttons)
	{
		window.draw(el);
	}
}
