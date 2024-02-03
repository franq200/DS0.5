#pragma once
#include "../DS0.5/IClock.h"
#include "gmock/gmock.h"

class ClockMock : public IClock
{
public:
	MOCK_METHOD(void, RestartClock, (), (override));
	MOCK_METHOD(float, GetElapsedTimeAsMilliseconds, (), (override));
};

