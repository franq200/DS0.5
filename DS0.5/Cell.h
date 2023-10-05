#pragma once
#include <SFML/Graphics.hpp>

enum class CellState : uint8_t
{
	Empty = 0,
	Filled,
	Teleport,
	Gate
};

class Cell : public sf::RectangleShape
{
public:
	Cell() = default;
	Cell(const sf::Vector2f& pos, CellState state);
	CellState GetState() const;
	void ChangeState(CellState newState);
private:
	CellState m_state;
};