#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

enum class CellType
{
	Empty = 0,
	Filled
};

class Map
{
public:
	void Init();
	void Draw(sf::RenderWindow& window);
private:
	void LoadMap();
	std::vector<std::vector<sf::RectangleShape>> m_map;
	std::vector<std::vector<CellType>> m_rawMap;
};

