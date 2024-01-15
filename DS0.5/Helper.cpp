#include "Helper.h"

namespace textures
{
	sf::Texture character;
	sf::Texture walkCharacter1;
	sf::Texture walkCharacter2;
	sf::Texture walkCharacter3;
	sf::Texture walkCharacter4;
	sf::Texture goblin1;
	sf::Texture goblin2;
	sf::Texture goblin3;
	sf::Texture goblin4;
	sf::Texture goblin5;
	sf::Texture warrior;
	sf::Texture dragon;
	sf::Texture start;
	sf::Texture exit;
	sf::Texture grass;
	sf::Texture rocks;
	sf::Texture wall;
	sf::Texture dirt;
	sf::Texture gate;
	sf::Texture teleport;
}

namespace position
{
	IndexPosition GetMapIndexesFromPosition(const sf::Vector2f& pos)
	{
		return { static_cast<size_t>(pos.x / size::cellSize), static_cast<size_t>(pos.y / size::cellSize) };
	}

	sf::Vector2f GetPositionFromMapIndexes(const std::pair<std::size_t, std::size_t>& mapIndexes)
	{
		return sf::Vector2f(mapIndexes.first * static_cast<float>(size::cellSize), mapIndexes.second * static_cast<float>(size::cellSize));
	}

	std::pair<int, int> Left(int x, int y)
	{
		return std::pair<int, int>(x - 1, y);
	}

	std::pair<int, int> Right(int x, int y)
	{
		return std::pair<int, int>(x + 1, y);
	}

	std::pair<int, int> Top(int x, int y)
	{
		return std::pair<int, int>(x, y + 1);
	}

	std::pair<int, int> Bottom(int x, int y)
	{
		return std::pair<int, int>(x, y - 1);
	}
}

namespace size
{
	float cellSize = 50.f;
	int windowSizeX = 1500;
	int windowSizeY = 750;
}

namespace character
{
	float damageTakenScaling = 1.f;
	float damageScaling = 1.f;
}