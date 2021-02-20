#include "Button.hpp"

Button::Button( ButtonTextures textures, UILabel* label, SDL_Rect rect, SDL_Renderer* renderer )
{   
    this->rect.x = rect.x;
    this->rect.y = rect.y;
    this->rect.w = rect.w;
    this->rect.h = rect.h;

    this->renderer = renderer;

    this->label = label;

    this->textures = textures;
}

Button::Button( ButtonTextures textures, UILabel* label, SDL_Rect rect, SDL_Renderer* renderer, const char* type, void (*summon)( SummonDungeon* dungeon, rapidjson::Value& json, const char* type ) ) : Button( textures, label, rect, renderer )
{
    this->SummonType = type;
    this->summon = summon;
}

Button::Button( ButtonTextures textures, UILabel* label, SDL_Rect rect, SDL_Renderer* renderer, void (*game)( Game* game ) ) : Button( textures, label, rect, renderer )
{
    this->game = game;
}

Button::Button( ButtonTextures textures, UILabel* label, SDL_Rect rect, SDL_Renderer* renderer, void (*item)( Shop* shop ) ) : Button( textures, label, rect, renderer )
{
    this->item = item;
}

void Button::Render()
{

    switch ( BUTTON_STATE )
    {
    case MOUSE_OUT:
        SDL_RenderCopy( renderer, textures.none, NULL, &rect );
        break;

    case MOUSE_OVER:
        SDL_RenderCopy( renderer, textures.over, NULL, &rect );
        break;

    case MOUSE_DOWN:
        SDL_RenderCopy( renderer, textures.down, NULL, &rect );
        break;
    }

    label->Render();
}

void Button::ChangeText(const char* text)
{
    label->ChangeText(text);
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