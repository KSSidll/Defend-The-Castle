#pragma once
#include "SummonDungeon.hpp"
#include "Button.hpp"

class UserInterface
{
private:
    std::deque<Button*> buttons;
    SDL_Renderer* renderer;
    SummonDungeon* dungeon;

public:
    UserInterface(rapidjson::Value& json, SummonDungeon* dungeon, SDL_Renderer* renderer);
    ~UserInterface();

    void Render();
    void HandleEvents(SDL_Event event);
};