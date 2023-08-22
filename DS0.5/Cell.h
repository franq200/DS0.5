#pragma once
#include <SFML/Graphics.hpp>

enum class CellState : uint8_t
{
	Empty = 0,
	Filled,
	Teleport
};

class Cell : public sf::RectangleShape
{
public:
	Cell() = default;
	Cell(sf::Vector2f size, sf::Vector2f pos, CellState state);
	CellState GetState() const;
private:
	CellState m_state;
};