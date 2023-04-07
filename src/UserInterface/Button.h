#pragma once
#include <SDL2/SDL.h>
#include <rapidjson/document.h>
#include <unordered_map>
#include "UILabel.h"

struct ButtonTextures;

class SummonDungeon;
class Game;
class Shop;

enum BUTTON_STATE{ MOUSE_OUT = 0, MOUSE_OVER = 1, MOUSE_DOWN = 2, MOUSE_UP = 3 };

class Button
{
private:
    template<typename> struct Type;
    BUTTON_STATE BUTTON_STATE = MOUSE_OUT;

    SDL_Renderer* renderer;
    SDL_Rect rect;

    ButtonTextures* textures;

    const void* Arg = nullptr;

public:
    Button();
    ~Button();

    Button( ButtonTextures* textures, SDL_Rect rect, SDL_Renderer* renderer );
    Button( ButtonTextures* textures, SDL_Rect rect, SDL_Renderer* renderer, void* type, void (*summon)( SummonDungeon* dungeon, rapidjson::Value& json, const char* type ) );
    Button( ButtonTextures* textures, SDL_Rect rect, SDL_Renderer* renderer, void (*game)( Game* game ) );
    Button( ButtonTextures* textures, SDL_Rect rect, SDL_Renderer* renderer, void* number, void (*game)( Game* game, float* number ) );
    Button( ButtonTextures* textures, SDL_Rect rect, SDL_Renderer* renderer, void* itemName, void (*item)( Shop* shop, const char* itemName ) );

    void Render();
    bool HandleEvents( SDL_Event* event );

    const void* GetArg(){ return Arg; };

    void (*summon)( SummonDungeon* dungeon, rapidjson::Value& json, const char* type) = nullptr;
    void (*game)( Game* game ) = nullptr;
    void (*game_numbered)( Game* game, float* number ) = nullptr;
    void (*item)( Shop* shop, const char* itemName ) = nullptr;
};

struct LabeledButton
{
    Button button;
    std::unordered_map<std::string, UILabel> labels;

    void Render()
    {
        button.Render();
        for( auto& label : labels )
        {
            label.second.Render();
        }
    }

    bool HandleEvents( SDL_Event* event )
    {
        return button.HandleEvents( event );
    }

    void ChangeText( std::string labelKey, const char* text )
    {
        labels.at( labelKey ).ChangeText( text );
    }

    const void* GetArg()
    {
        return button.GetArg();
    }
};
