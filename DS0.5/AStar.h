#pragma once
#include <SFML/Graphics.hpp>
#include "Helper.h"

namespace aStar
{
	std::vector<sf::Vector2f> FindShortestPath(const IndexPosition& characterIndex,
		const IndexPosition& enemyIndex,
		const std::vector<std::vector<bool>>& map);
}
