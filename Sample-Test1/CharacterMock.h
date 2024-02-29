#pragma once
#include <SFML/Graphics.hpp>
#include "../DS0.5/ICharacter.h"
#include <gmock/gmock.h>

class CharacterMock : public ICharacter
{
public:
	CharacterMock(std::unique_ptr<IHpBar> hpBar, std::unique_ptr<IClock> clock) :
		ICharacter(std::move(hpBar), std::move(clock))
    {
    }
	MOCK_METHOD(void, Teleport, (const sf::Vector2f& newPosition), (override));
	MOCK_METHOD(bool, IsAbleToAttack, (), (override));
	MOCK_METHOD(void, Init, (sf::Vector2f spawnPos), (override));
	MOCK_METHOD(void, MakeMove, (const sf::Vector2f& moveValue), (override));
	MOCK_METHOD(void, Attack, (Enemy& enemy), (override));
	MOCK_METHOD(void, Restart, (), (override));
	MOCK_METHOD(int, GetMoveDistance, (), (const override));
	MOCK_METHOD(std::vector<sf::Vector2f>, GetEveryPossibleMovement, (), (const override));
	MOCK_METHOD(bool, IsSlowed, (), (override));
	MOCK_METHOD(bool, IsLeftMovePossible, (const Map* map), (const override));
	MOCK_METHOD(bool, IsRightMovePossible, (const Map* map), (const override));
	MOCK_METHOD(bool, IsUpMovePossible, (const Map* map), (const override));
	MOCK_METHOD(bool, IsDownMovePossible, (const Map* map), (const override));
	MOCK_METHOD(void, UpdateHpBarPos, (), (override));
	MOCK_METHOD(sf::Vector2f, GetPositionWithRotate, (), (const override));
};

