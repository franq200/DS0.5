#pragma once
#include <SFML/Graphics.hpp>
#include "Fightable.h"
#include "Moveable.h"

class ICharacter;
class IClock;

class Enemy : public Fightable, public Moveable
{
public:
	Enemy(Damage attackDamage, Hp startHp, float scale, AttackRange attackRange, AttackSpeed attackSpeed, const std::vector<std::reference_wrapper<sf::Texture>>& textures, std::unique_ptr<IHpBar> hpBar, std::unique_ptr<IClock> clock);
	void Init(const sf::Vector2f& spawnPos);
	void Restart();
	void TryKill(ICharacter& character);
	void Attack(ICharacter& character);
	void PreparePathAndMove(const sf::Vector2f& characterPos, const std::vector<std::vector<bool>>& map);
	void UpdateHpBarPos() override;
protected:
	virtual void Kill(ICharacter& character) = 0;
	sf::Vector2f m_spawnPos;
	std::vector<sf::Vector2f> m_pathToCharacter;
	bool m_isAttackClockRestarted = false;
private:
	void Move();
	void ChooseDirection();
	Direction m_moveDirection;
};