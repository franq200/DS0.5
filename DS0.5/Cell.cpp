#include "Cell.h"
#include "Helper.h"

Cell::Cell(const sf::Vector2f& pos, const CellState& state) :
m_state(state)
{
	setSize({size::cellSize, size::cellSize});
	setPosition(pos);
	SetTexture();
}

CellState Cell::GetState() const
{
	return m_state;
}

void Cell::ChangeState(CellState newState)
{
	m_state = newState;
	SetTexture();
}

void Cell::SetTexture()
{
	switch (m_state)
	{
	case CellState::Empty:
		setFillColor(sf::Color::Green);
		break;
	case CellState::Filled:
		setFillColor(sf::Color::Red);
		break;
	case CellState::Teleport:
		setFillColor(sf::Color::Blue);
		break;
	case CellState::CloseGate:
		setFillColor(sf::Color::Yellow);
		break;
	case CellState::OpenGate:
		setFillColor(sf::Color::Green);
	}
}
