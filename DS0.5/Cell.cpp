#include "Cell.h"

Cell::Cell(const sf::Vector2f& size, const sf::Vector2f& pos, CellState state) :
m_state(state)
{
	setSize(size);
	setPosition(pos);

	if (state == CellState::Empty) // switch case
	{
		setFillColor(sf::Color::Green);
	}
	else if (state == CellState::Filled)
	{
		setFillColor(sf::Color::Red);
	}
	else if (state == CellState::Teleport)
	{
		setFillColor(sf::Color::Blue);
	}
	else if (state == CellState::Gate)
	{
		setFillColor(sf::Color::Yellow);
	}
}

CellState Cell::GetState() const
{
	return m_state;
}

void Cell::ChangeState(CellState newState)
{
	m_state = newState;
	setFillColor(sf::Color::Green);
}
