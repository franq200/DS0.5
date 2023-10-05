#pragma once
#include <SFML/Graphics.hpp>

class HpBar
{
public:
	void Init(const sf::Vector2f& characterPos, float hp);
	void SetPosition(const sf::Vector2f& goblinPos);
	void ChangeHpLevel();
	void Draw(sf::RenderWindow& window);
	bool IsDead();
	void LossHp(float lostHp);
	void GainHp(float gainedHp);
	void IncreaseMaxHp(float hpToIncrease);
private:
	void Rescale();
	sf::RectangleShape m_hpBarBackground;
	sf::RectangleShape m_hpBar;
	float m_hp;
};
