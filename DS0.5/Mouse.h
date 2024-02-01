#pragma once
#include "SFML/Graphics.hpp"

class IMouse
{
public:
    virtual ~IMouse() = default;
    virtual bool IsLeftButtonPressed() = 0;
};

class Mouse : public IMouse
{
	public:
    bool IsLeftButtonPressed() override
    {
        return sf::Mouse::isButtonPressed(sf::Mouse::Left);
    }

    private:
    sf::Mouse m_mouse;
};

