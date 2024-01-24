#pragma once
#include "..\DS0.5\Mouse.h"
#include "gmock/gmock.h"

class MouseMock : public IMouse
{
	MOCK_METHOD(bool, isButtonPressed, (Button button), ());
};

