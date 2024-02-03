#include "gtest/gtest.h"
#include "..\DS0.5\Character.h"
#include "HpBarMock.h"
#include "MouseMock.h"
#include "ClockMock.h"
#include "../DS0.5/Warrior.h"

class BasicDsTests : public testing::Test
{
protected:
	std::unique_ptr<testing::NiceMock<HpBarMock>> hpBarMock{ std::make_unique<testing::NiceMock<HpBarMock>>() };
	std::unique_ptr<testing::NiceMock<MouseMock>> mouseMock{ std::make_unique<testing::NiceMock<MouseMock>>() };
	std::unique_ptr<testing::NiceMock<ClockMock>> clockMock{ std::make_unique<testing::NiceMock<ClockMock>>() };
};

class CharacterTests : public BasicDsTests
{
protected:
	Character createSut()
	{
		return { std::move(hpBarMock), std::move(mouseMock), std::move(clockMock)};
	}
};


TEST_F(CharacterTests, CharacterPositionAfterTeleportTest) {
	EXPECT_CALL(*hpBarMock, SetPosition(testing::_)).Times(1);

	auto sut = createSut();
	sut.Teleport({ 162.f, 170.f });

	EXPECT_EQ(sut.getPosition().x, 162.f);
	EXPECT_EQ(sut.getPosition().y, 170.f);
}

TEST_F(CharacterTests, MouseIsButtonPressedTest)
{
	//given
	EXPECT_CALL(*mouseMock, IsLeftButtonPressed()).Times(testing::AtLeast(1)).WillOnce(testing::Return(true)).WillOnce(testing::Return(false)).WillOnce(testing::Return(false));
	auto warriorHpBarMock = std::make_unique<testing::StrictMock<HpBarMock>>();
	EXPECT_CALL(*warriorHpBarMock, Init(testing::_, testing::_, testing::_)).Times(testing::AtLeast(1));
	EXPECT_CALL(*warriorHpBarMock, LossHp(testing::_)).Times(testing::AtLeast(1));
	EXPECT_CALL(*warriorHpBarMock, IsDead()).Times(testing::AtLeast(1));
	//when
	auto sut = createSut();
	const bool firstAttackIsAble = sut.IsAbleToAttack();
	const bool secondAttackIsForbidden = sut.IsAbleToAttack();
	//then
	EXPECT_TRUE(firstAttackIsAble);
	EXPECT_FALSE(secondAttackIsForbidden);

	//given
	Warrior warrior(std::move(warriorHpBarMock), std::move(clockMock));
	warrior.Init(sut.getPosition());
	//when
	sut.Attack(warrior);
	const bool attackIsForbidden = sut.IsAbleToAttack();
	//then
	EXPECT_FALSE(attackIsForbidden);
}

TEST_F(CharacterTests, GetEveryPossibleMovementTest)
{
	//given
	const int moveDistance = 3;
	const std::vector<sf::Vector2f> expectedMovement = { {500.f + moveDistance, 500.f}, {500.f - moveDistance, 500.f}, {500.f, 500.f - moveDistance}, {500.f, 500.f + moveDistance} };
	//when
	auto sut = createSut();
	sut.setPosition(500.f, 500.f);
	std::vector<sf::Vector2f> movement = sut.GetEveryPossibleMovement();
	//then
	EXPECT_EQ(movement, expectedMovement);
}

class WarriorTest : public BasicDsTests
{
protected:
	Warrior createSut()
	{
		return { std::move(hpBarMock), std::move(clockMock)};
	}
};

TEST_F(WarriorTest, InitTest)
{
	EXPECT_CALL(*hpBarMock, Init(testing::_, testing::_, testing::_)).Times(testing::AtLeast(1));
	Warrior warrior = createSut();
	warrior.Init({ 100.f, 100.f });
}

TEST_F(WarriorTest, RestartTest)
{
	EXPECT_CALL(*hpBarMock, Restart(testing::_, testing::_)).Times(testing::AtLeast(1));
	Warrior warrior = createSut();
	warrior.Restart();
}

TEST_F(WarriorTest, AttackTest)
{
	EXPECT_CALL(*clockMock, RestartClock()).Times(2);
	EXPECT_CALL(*clockMock, GetElapsedTimeAsMilliseconds()).Times(testing::AtLeast(1)).WillRepeatedly(testing::Return(700.f));
	Warrior warrior = createSut();
	warrior.Init({ 100.f, 100.f });

	std::unique_ptr<testing::NiceMock<HpBarMock>> hpBarMockCharacter{ std::make_unique<testing::NiceMock<HpBarMock>>() };
	std::unique_ptr<testing::NiceMock<ClockMock>> clockMockCharacter{ std::make_unique<testing::NiceMock<ClockMock>>() };
	Character character(std::move(hpBarMockCharacter), std::move(mouseMock), std::move(clockMockCharacter));
	character.Init({ 100.f, 100.f });

	warrior.Attack(character);
	warrior.Attack(character);
}