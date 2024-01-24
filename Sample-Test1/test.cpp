#include "gtest/gtest.h"
#include "..\DS0.5\Character.h"
#include "HpBarMock.h"
#include "MouseMock.h"

TEST(CharacterTest, CharacterPositionAfterTeleportTest) {
	auto hpBarMock = std::make_unique<HpBarMock>();
	EXPECT_CALL(*hpBarMock, SetPosition(testing::_)).Times(1);

	Character character(std::move(hpBarMock));
	character.Teleport({162.f, 170.f});

	
	EXPECT_EQ(character.getPosition().x, 162.f);
	EXPECT_EQ(character.getPosition().y, 170.f);
}

TEST(MouseTest, MouseIsButtonPressedTest)
{
	auto mouseMock = std::make_unique<MouseMock>();
	EXPECT_CALL(*mouseMock, isButtonPressed(testing::_)).Times(1);
}