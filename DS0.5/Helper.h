#pragma once
#include <SFML/Graphics.hpp>
#include <optional>

using DirectionResult = std::optional< std::vector<sf::Vector2f>>;
using IndexPosition = std::pair<size_t, size_t>;

namespace textures
{
	extern sf::Texture character;
	extern sf::Texture walkCharacter1;
	extern sf::Texture walkCharacter2;
	extern sf::Texture walkCharacter3;
	extern sf::Texture walkCharacter4;
	extern sf::Texture goblin1;
	extern sf::Texture goblin2;
	extern sf::Texture goblin3;
	extern sf::Texture goblin4;
	extern sf::Texture goblin5;
	extern sf::Texture warrior;
	extern sf::Texture dragon;
	extern sf::Texture start;
	extern sf::Texture exit;
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
	IndexPosition GetMapIndexesFromPosition(const sf::Vector2f&);
	sf::Vector2f GetPositionFromMapIndexes(const std::pair<std::size_t, std::size_t>&);

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
