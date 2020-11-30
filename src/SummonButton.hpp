#pragma once
#include "SummonDungeon.hpp"

enum state{ nothing = 0, hover = 1, press = 2 };

class Button
{
private:
    SDL_Renderer* renderer;
    state state;
    SDL_Rect rect;
    rapidjson::Value* entityDoc;
    SummonDungeon* dungeon;

public:
    Button( SDL_Rect rect, SDL_Renderer* renderer, SummonDungeon* dungeon, rapidjson::Value* entityDoc );
    ~Button();

    void Render();
};