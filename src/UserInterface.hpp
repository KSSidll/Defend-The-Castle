#pragma once
#include "SummonDungeon.hpp"
#include "TextureManager.hpp"
#include "Button.hpp"

class UserInterface
{
private:
    const bool* paused;

    rapidjson::Value json;
    SDL_Renderer* renderer;
    SummonDungeon* dungeon;
    std::deque<Button*> summonButtons;
    std::deque<Button*> menuButtons;

public:
    UserInterface( rapidjson::Value& json, SummonDungeon* dungeon, SDL_Renderer* renderer, const bool* paused );
    ~UserInterface();

    void Render();
    void HandleEvents( SDL_Event* event );
};