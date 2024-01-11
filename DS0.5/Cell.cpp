#include "Cell.h"
#include "Helper.h"

Cell::Cell(const sf::Vector2f& pos, const CellState& state, const sf::Texture* texture) :
m_state(state)
{
	setTexture(texture);
	setSize({size::cellSize, size::cellSize});
	setPosition(pos);
}

CellState Cell::GetState() const
{
	return m_state;
}

void Cell::SetCellOpen()
{
	m_state = CellState::OpenGate;
	setTexture(&textures::dirt);
}

void Cell::SetCellClosed()
{
	m_state = CellState::CloseGate;
	setTexture(&textures::gate);
}
