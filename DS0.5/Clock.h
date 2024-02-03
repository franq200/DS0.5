#pragma once
#include "IClock.h"
#include <SFML/Graphics.hpp>

class Clock : public IClock
{
public:
	void RestartClock();
	float GetElapsedTimeAsMilliseconds();
private:
	sf::Clock m_clock;
};

