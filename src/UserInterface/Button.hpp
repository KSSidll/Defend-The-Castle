#pragma once
#include "../Managers/SummonDungeon.hpp"

enum BUTTON_STATE{ MOUSE_OUT = 0, MOUSE_OVER = 1, MOUSE_DOWN = 2, MOUSE_UP = 3 };

class Button
{
private:
    BUTTON_STATE BUTTON_STATE = MOUSE_OUT;

    SDL_Renderer* renderer;
    SDL_Rect rect;

    ButtonTextures textures;
    SDL_Texture* text;

public:
    Button( ButtonTextures textures, SDL_Texture* text, SDL_Rect rect, SDL_Renderer* renderer );
    Button( ButtonTextures textures, SDL_Texture* text, SDL_Rect rect, SDL_Renderer* renderer, void (*callback)( SummonDungeon* dungeon, rapidjson::Value& json ) );
    ~Button(){};

    void Render();
    bool HandleEvents( SDL_Event* event );

    void (*callback)( SummonDungeon* dungeon, rapidjson::Value& json );
};