#pragma once
#include "SummonDungeon.hpp"
#include "TextureManager.hpp"
#include "SummonButton.hpp"

class UserInterface
{
private:
    const bool* paused;
    std::deque<SummonButton*> buttons;
    SDL_Renderer* renderer;
    SummonDungeon* dungeon;

public:
    UserInterface( rapidjson::Value& json, SummonDungeon* dungeon, SDL_Renderer* renderer, const bool* paused );
    ~UserInterface();

    void Render();
    void HandleEvents( SDL_Event* event );
};