#pragma once
#include <SFML/Graphics.hpp>

namespace textures
{
	extern sf::Texture character;
	extern sf::Texture walkCharacter1;
	extern sf::Texture walkCharacter2;
	extern sf::Texture walkCharacter3;
	extern sf::Texture walkCharacter4;

	extern sf::Texture goblin;
	extern sf::Texture walkGoblin1;
	extern sf::Texture walkGoblin2;
	extern sf::Texture walkGoblin3;
	extern sf::Texture walkGoblin4;
	
	extern sf::Texture warrior;

	extern sf::Texture dragon;
}

namespace speed
{
	extern float character;
	extern float enemy;
	extern float enemyAttackSpeed;
	extern float characterAttackSpeed;
}

namespace enemy
{
	extern const float defaultGoblinHp;
	extern const float defaultWarriorHp;
	extern const float defaultDragonHp;
}

namespace position
{
	std::pair<std::size_t, std::size_t> GetMapIndexesFromPosition(const sf::Vector2f&);
	sf::Vector2f GetPositionFromMapIndexes(const std::pair<std::size_t, std::size_t>&);

	double CalculateDistance(std::pair<size_t, size_t> start, std::pair<size_t, size_t> end);

	std::pair<int, int> Left(int x, int y);
	std::pair<int, int> Right(int x, int y);
	std::pair<int, int> Top(int x, int y);
	std::pair<int, int> Bottom(int x, int y);
}

namespace size
{
	extern float cellSize;
	extern int windowSizeX;
	extern int windowSizeY;
}

namespace character
{
	extern float damageTakenScaling;
	extern float damageScaling;
	extern float defaultScale;
	extern float defaultHp;
	extern float moveRange;
	extern float attackDamage;
}
