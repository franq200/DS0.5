#include <gmock/gmock.h>
#include "..\DS0.5\HpBar.h"

class HpBarMock : public IHpBar
{
	public:
		MOCK_METHOD(void, SetPosition, (const sf::Vector2f& goblinPos), (override));
		MOCK_METHOD(void, Init, (const sf::Vector2f& characterPos, float hp, const sf::Vector2f& characterSize), (override));
		MOCK_METHOD(void, Restart, (const sf::Vector2f& characterPos, float hp), (override));
		MOCK_METHOD(void, RescaleHp, (), (override));
		MOCK_METHOD(void, Draw, (sf::RenderWindow& window), (override));
		MOCK_METHOD(bool, IsDead, (), (override));
		MOCK_METHOD(void, LossHp, (float lostHp), (override));
		MOCK_METHOD(void, GainHp, (float gainedHp), (override));
		MOCK_METHOD(void, SetNewMaxHp, (float newHp), (override));
};