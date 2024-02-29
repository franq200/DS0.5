#pragma once
#include <SFML/Graphics.hpp>

enum class HpBarPosition
{
	underCharacter = 0,
	LeftTopCorner
};


class IHpBar
{
public:
	virtual ~IHpBar() = default;
	virtual void Init(const sf::Vector2f& characterPos, float hp, const sf::Vector2f& characterSize, const HpBarPosition& hpBarPos) = 0;
	virtual void Restart(const sf::Vector2f& characterPos, float hp) = 0;
	virtual void SetPosition(const sf::Vector2f& goblinPos) = 0;
	virtual void RescaleHp() = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;
	virtual bool IsDead() = 0;
	virtual void LossHp(float lostHp) = 0;
	virtual void GainHp(float gainedHp) = 0;
	virtual void SetNewMaxHp(float newHp) = 0;
	/*
	void* vtable{&Init, &Restart, ...}
	*/
};


class HpBar : public IHpBar
{
public:
	void Init(const sf::Vector2f& characterPos, float hp, const sf::Vector2f& characterSize, const HpBarPosition& hpBarPos) override;
	void Restart(const sf::Vector2f& characterPos, float hp) override;
	void SetPosition(const sf::Vector2f& goblinPos) override;
	void RescaleHp() override;
	void Draw(sf::RenderWindow& window) override;
	bool IsDead() override;
	void LossHp(float lostHp) override;
	void GainHp(float gainedHp) override;
	void SetNewMaxHp(float newHp) override;
private:
	void SetLeftTopCornerPos();
	void SetUnderCharacter(const sf::Vector2f& characterPos);
	void Rescale();
	HpBarPosition m_hpBarRelativePosition;
	sf::Vector2f m_characterSize;
	sf::RectangleShape m_hpBarBackground;
	sf::RectangleShape m_hpBar;
	float m_hp;
};
