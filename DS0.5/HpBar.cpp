#include "HpBar.h"

void HpBar::Init(const sf::Vector2f& goblinPos)
{
	SetPosition(goblinPos);

	m_hpBarBackground.setSize({ 50.f, 16.f });
	m_hpBarBackground.setFillColor(sf::Color(60, 50, 50, 160));

	m_hpBar.setSize({ 46.f, 12.f });
	m_hpBar.setFillColor(sf::Color(210, 50, 50, 230));
}

void HpBar::SetPosition(const sf::Vector2f& goblinPos)
{
	m_hpBarBackground.setPosition(goblinPos.x, goblinPos.y + 50.f);
	m_hpBar.setPosition(goblinPos.x + 2, goblinPos.y + 52.f);
}

void HpBar::ChangeHpLevel(const float& hp)
{
	m_hpBar.setScale(hp / 100.f, 1.f);
}

void HpBar::Draw(sf::RenderWindow& window)
{
	window.draw(m_hpBarBackground);
	window.draw(m_hpBar);
}
