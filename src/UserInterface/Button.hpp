#pragma once
#include "../Managers/SummonDungeon.hpp"
#include "../Managers/TextureManager.hpp"
#include "../Managers/Shop.hpp"
#include "UILabel.hpp"
#include "../Engine/Game.hpp"

class Game;

enum BUTTON_STATE{ MOUSE_OUT = 0, MOUSE_OVER = 1, MOUSE_DOWN = 2, MOUSE_UP = 3 };

class Button
{
private:
    BUTTON_STATE BUTTON_STATE = MOUSE_OUT;

    SDL_Renderer* renderer;
    SDL_Rect rect;

    ButtonTextures textures;

    const char* SummonType = nullptr;

public:
    Button();
    ~Button();
    
    Button( ButtonTextures textures, SDL_Rect rect, SDL_Renderer* renderer );
    Button( ButtonTextures textures, SDL_Rect rect, SDL_Renderer* renderer, const char* type, void (*summon)( SummonDungeon* dungeon, rapidjson::Value& json, const char* type ) );
    Button( ButtonTextures textures, SDL_Rect rect, SDL_Renderer* renderer, void (*game)( Game* game ) );
    Button( ButtonTextures textures, SDL_Rect rect, SDL_Renderer* renderer, void (*item)( Shop* shop ) );

    void Render();
    bool HandleEvents( SDL_Event* event );

    const char* GetType(){ return SummonType; };

    void (*summon)( SummonDungeon* dungeon, rapidjson::Value& json, const char* type) = nullptr;
    void (*game)( Game* game ) = nullptr;
    void (*item)( Shop* shop ) = nullptr;
};