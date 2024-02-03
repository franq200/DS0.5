#include "Clock.h"

void Clock::RestartClock()
{
	m_clock.restart();
}

float Clock::GetElapsedTimeAsMilliseconds()
{
	return static_cast<float>(m_clock.getElapsedTime().asMilliseconds());
}
