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
}

namespace speed
{
	extern float character;
}

namespace position
{
	std::pair<std::size_t, std::size_t> GetMapIndexesFromPosition(const sf::Vector2f&);
	sf::Vector2f GetPositionFromMapIndexes(const std::pair<std::size_t, std::size_t>&);

	double CalculateDistance(std::pair<size_t, size_t> start, std::pair<size_t, size_t> end);
}