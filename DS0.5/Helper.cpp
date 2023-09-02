#include "Helper.h"

namespace textures
{
	sf::Texture character;
	sf::Texture walkCharacter1;
	sf::Texture walkCharacter2;
	sf::Texture walkCharacter3;
	sf::Texture walkCharacter4;

	sf::Texture goblin;
	sf::Texture walkGoblin1;
	sf::Texture walkGoblin2;
	sf::Texture walkGoblin3;
	sf::Texture walkGoblin4;

	sf::Texture warrior;
}

namespace speed
{
	float character = 100.f;
	float enemy = 600.f;
	float enemyAttackSpeed = 700.f;
	float characterAttackSpeed = 300.f;
}

namespace position
{
	std::pair<std::size_t, std::size_t> GetMapIndexesFromPosition(const sf::Vector2f& pos)
	{
		return { static_cast<size_t>(pos.x / 50), static_cast<size_t>(pos.y / 50) };
	}

	sf::Vector2f GetPositionFromMapIndexes(const std::pair<std::size_t, std::size_t>& mapIndexes)
	{
		return sf::Vector2f(mapIndexes.first * static_cast<float>(50), mapIndexes.second * static_cast<float>(50));
	}

	double CalculateDistance(std::pair<size_t, size_t> start, std::pair<size_t, size_t> end)
	{
		double xPos = static_cast<double>(start.first) - end.first;
		double yPos = static_cast<double>(start.second) - end.second;
		return std::abs(xPos) + std::abs(yPos);
	}

}

namespace size
{
	float cellSize = 50.f;
	float windowSizeX = 1500.f;
	float windowSizeY = 750.f;
}

namespace character
{
	float damageTakenScaling = 1.f;
	float damageScaling = 1.f;
}

