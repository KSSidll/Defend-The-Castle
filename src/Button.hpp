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

    void (*callback)();
    Button(rapidjson::Value& json, SDL_Renderer* renderer);

public:
    Button(rapidjson::Value& json, SDL_Renderer* renderer, void (*callback)());
    Button(rapidjson::Value& json, SDL_Renderer* renderer, void (*callback)(), rapidjson::Value& entityDoc);
    ~Button();

    void Render();
};