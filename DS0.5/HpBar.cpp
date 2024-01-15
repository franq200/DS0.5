#include "HpBar.h"

void HpBar::Init(const sf::Vector2f& characterPos, float hp, const sf::Vector2f& characterSize)
{
	m_characterSize = characterSize;
	m_hp = hp;
	m_hpBar.setSize({ m_hp / 100.f*46.f, 12.f });
	m_hpBar.setFillColor(sf::Color(210, 50, 50, 230));
	m_hpBarBackground.setSize({ m_hpBar.getSize().x * m_hp / 100.f + 4.f, 16.f });
	m_hpBarBackground.setFillColor(sf::Color(60, 50, 50, 160));
	Rescale();
	SetPosition(characterPos);
}

void HpBar::Restart(const sf::Vector2f& characterPos, float hp)
{
	m_hp = hp;
	Rescale();
	SetPosition(characterPos);
}

void HpBar::SetPosition(const sf::Vector2f& characterPos)
{
	int hpBarDifference = static_cast<int>(m_hpBar.getSize().x - m_characterSize.x)/2;
	m_hpBar.setPosition(characterPos.x - hpBarDifference + 2, characterPos.y + m_characterSize.y + 2);
	m_hpBarBackground.setPosition(m_hpBar.getPosition().x - 2, characterPos.y + m_characterSize.y);
}

void HpBar::RescaleHp()
{
	m_hpBar.setScale(m_hp / 100.f, 1.f);
}

void HpBar::Rescale()
{
	m_hpBar.setSize({ m_hp / 100.f * 46.f, 12.f });
	m_hpBarBackground.setSize({ m_hpBar.getSize().x + 4 / 100.f + 4.f, 16.f });
}

void HpBar::Draw(sf::RenderWindow& window)
{
	window.draw(m_hpBarBackground);
	window.draw(m_hpBar);
}

bool HpBar::IsDead()
{
	return m_hp <= 0;
}

void HpBar::LossHp(float lostHp)
{
	m_hp -= lostHp;
	RescaleHp();
}

void HpBar::GainHp(float gainedHp)
{
	m_hp += gainedHp;
	RescaleHp();
}

void HpBar::IncreaseMaxHp(float hpToIncrease)
{
	m_hp += hpToIncrease;
	Rescale();
}

void HpBar::SetHp(float newHp)
{
	m_hp = newHp;
	Rescale();
}
