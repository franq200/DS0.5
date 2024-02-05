#pragma once
#include "IClock.h"
#include <SFML/Graphics.hpp>

class Clock : public IClock
{
public:
	void RestartClock() override;
	float GetElapsedTimeAsMilliseconds() override;
private:
	sf::Clock m_clock;
};

