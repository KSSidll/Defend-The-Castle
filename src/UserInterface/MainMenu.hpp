#pragma once
#include "Button.hpp"
#include <deque>

class MainMenu
{
    private:
        std::deque<Button*> buttons;

    public:
        MainMenu(){};
        ~MainMenu(){};
};