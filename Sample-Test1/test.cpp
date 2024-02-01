#include "gtest/gtest.h"
#include "..\DS0.5\Character.h"
#include "HpBarMock.h"
#include "MouseMock.h"
#include "../DS0.5/Warrior.h"

TEST(CharacterTest, CharacterPositionAfterTeleportTest) {
	auto hpBarMock = std::make_unique<HpBarMock>();
	EXPECT_CALL(*hpBarMock, SetPosition(testing::_)).Times(1);

	Character character(std::move(hpBarMock), std::make_unique<MouseMock>());
	character.Teleport({162.f, 170.f});

	
	EXPECT_EQ(character.getPosition().x, 162.f);
	EXPECT_EQ(character.getPosition().y, 170.f);
}

TEST(MouseTest, MouseIsButtonPressedTest)
{
	auto mouseMock = std::make_unique<MouseMock>();
	EXPECT_CALL(*mouseMock, IsLeftButtonPressed()).Times(testing::AtLeast(1)).WillOnce(testing::Return(true)).WillOnce(testing::Return(false)).WillOnce(testing::Return(false));
	
	Character character(std::make_unique<HpBarMock>(), std::move(mouseMock));
	EXPECT_TRUE(character.IsAbleToAttack());
	EXPECT_FALSE(character.IsAbleToAttack());

	auto warriorHpBarMock = std::make_unique<HpBarMock>();
	EXPECT_CALL(*warriorHpBarMock, Init(testing::_, testing::_, testing::_)).Times(testing::AtLeast(1));
	EXPECT_CALL(*warriorHpBarMock, LossHp(testing::_)).Times(testing::AtLeast(1));
	EXPECT_CALL(*warriorHpBarMock, IsDead()).Times(testing::AtLeast(1));
	Warrior warrior(std::move(warriorHpBarMock));
	warrior.Init(character.getPosition());
	character.Attack(warrior);
	EXPECT_FALSE(character.IsAbleToAttack());
}