#include "../Managers/TextureManager.hpp"
#include "../Managers/Shop.hpp"
#include "../Managers/SummonDungeon.hpp"
#include "../Engine/Game.hpp"
#include "Button.hpp"
#include "UILabel.hpp"

Button::Button()
{
    renderer = nullptr;
    textures = nullptr;
}

Button::~Button()
{
    textures = nullptr;
    summon = nullptr;
    game = nullptr;
    item = nullptr;
    Arg = nullptr;
    renderer = nullptr;
}

Button::Button( ButtonTextures* textures, SDL_Rect rect, SDL_Renderer* renderer )
{   
    this->rect.x = rect.x;
    this->rect.y = rect.y;
    this->rect.w = rect.w;
    this->rect.h = rect.h;

    this->renderer = renderer;

    this->textures = textures;
}

Button::Button( ButtonTextures* textures, SDL_Rect rect, SDL_Renderer* renderer, void* type, void (*summon)( SummonDungeon* dungeon, rapidjson::Value& json, const char* type ) ) : Button( textures, rect, renderer )
{
    Arg = type;
    this->summon = summon;
}

Button::Button( ButtonTextures* textures, SDL_Rect rect, SDL_Renderer* renderer, void (*game)( Game* game ) ) : Button( textures, rect, renderer )
{
    this->game = game;
}

Button::Button( ButtonTextures* textures, SDL_Rect rect, SDL_Renderer* renderer, void* number, void (*game)( Game* game, float* number ) ) : Button( textures, rect, renderer )
{
    Arg = number;
    this->game_numbered = game;
}

Button::Button( ButtonTextures* textures, SDL_Rect rect, SDL_Renderer* renderer, void (*item)( Shop* shop ) ) : Button( textures, rect, renderer )
{
    this->item = item;
}

void Button::Render()
{

    switch ( BUTTON_STATE )
    {
    case MOUSE_OUT:
        SDL_RenderCopy( renderer, textures->none, NULL, &rect );
        break;

    case MOUSE_OVER:
        SDL_RenderCopy( renderer, textures->over, NULL, &rect );
        break;

    case MOUSE_DOWN:
        SDL_RenderCopy( renderer, textures->down, NULL, &rect );
        break;
    }
}

bool Button::HandleEvents( SDL_Event* event )
{
    if( event->type == SDL_MOUSEMOTION || event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP )
    {
        int x, y;
        bool inside = true;
        SDL_GetMouseState( &x, &y );

        if( x < rect.x )
            inside = false;
        else if( x > rect.x + rect.w )
            inside = false;
        else if( y < rect.y )
            inside = false;
        else if( y > rect.y + rect.h )
            inside = false;

        if( !inside )
            BUTTON_STATE = MOUSE_OUT;
        else if( BUTTON_STATE == MOUSE_OUT )
            BUTTON_STATE = MOUSE_OVER;
    }
    
    if( event->type == SDL_MOUSEBUTTONDOWN )
    {
        if( BUTTON_STATE == MOUSE_OVER )
            BUTTON_STATE = MOUSE_DOWN;
    }

    if( event->type == SDL_MOUSEBUTTONUP )
    {
        if( BUTTON_STATE == MOUSE_DOWN )
            BUTTON_STATE = MOUSE_UP;
    }

    if( BUTTON_STATE == MOUSE_UP )
    {
        BUTTON_STATE = MOUSE_OVER;
        return true;
    }
    return false;
}