#include "HpBar.h"

void HpBar::Init(const sf::Vector2f& characterPos, float hp)
{
	m_hp = hp;
	SetPosition(characterPos);

	m_hpBarBackground.setSize({ 50.f, 16.f });
	m_hpBarBackground.setFillColor(sf::Color(60, 50, 50, 160));
	m_hpBarBackground.setScale(hp / 100.f, 1.f);

	m_hpBar.setSize({ 46.f, 12.f });
	m_hpBar.setFillColor(sf::Color(210, 50, 50, 230));
	m_hpBar.setScale(hp / 100.f, 1.f);
	Rescale();
}

void HpBar::SetPosition(const sf::Vector2f& characterPos)
{
	m_hpBarBackground.setPosition(characterPos.x, characterPos.y + 50.f);
	m_hpBar.setPosition(characterPos.x + 2, characterPos.y + 52.f);
}

void HpBar::ChangeHpLevel()
{
	m_hpBar.setScale(m_hp / 100.f, 1.f);
}

void HpBar::Rescale()
{
	m_hpBar.setScale(m_hp / 100.f, 1.f);
	m_hpBarBackground.setSize({ m_hpBar.getSize().x * m_hp / 100.f + 4.f, 16.f});
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
	ChangeHpLevel();
}

void HpBar::GainHp(float gainedHp)
{
	m_hp += gainedHp;
	ChangeHpLevel();
}

void HpBar::IncreaseMaxHp(float hpToIncrease)
{
	m_hp += hpToIncrease;
	Rescale();
}
