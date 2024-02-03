#pragma once
class IClock
{
public:
	virtual ~IClock() = default;
	virtual void RestartClock() = 0;
	virtual float GetElapsedTimeAsMilliseconds() = 0;
};

