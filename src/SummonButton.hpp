#pragma once
#include "SummonDungeon.hpp"

enum BUTTON_STATE{ MOUSE_OUT = 0, MOUSE_OVER = 1, MOUSE_DOWN = 2, MOUSE_UP = 3 };

class SummonButton
{
private:
    SDL_Renderer* renderer;
    BUTTON_STATE BUTTON_STATE = MOUSE_OUT;
    SDL_Rect rect;
    rapidjson::Value* entityDoc;
    SummonDungeon* dungeon;

public:
    SummonButton( SDL_Rect rect, SDL_Renderer* renderer, SummonDungeon* dungeon, rapidjson::Value* entityDoc );
    ~SummonButton(){};

    void Render();
    void HandleEvents( SDL_Event* event );
};