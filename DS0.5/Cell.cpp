#include "Cell.h"

Cell::Cell(sf::Vector2f size, sf::Vector2f pos, CellState state) :
m_state(state)
{
	setSize(size);
	setPosition(pos);
	if (state == CellState::Empty)
	{
		setFillColor(sf::Color::Green);
	}
	else
	{
		setFillColor(sf::Color::Red);
	}
}

CellState Cell::GetState() const
{
	return m_state;
}
