#pragma once
#include "..\DS0.5\Mouse.h"
#include "gmock/gmock.h"

class MouseMock : public IMouse
{
public:
	MOCK_METHOD(bool, IsLeftButtonPressed, (), (override));
};

