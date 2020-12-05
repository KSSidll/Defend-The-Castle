#pragma once
#include "Button.hpp"
#include <deque>

class PauseMenu
{
    private:
        std::deque<Button*> buttons;

    public:
        PauseMenu(){};
        ~PauseMenu(){};
};