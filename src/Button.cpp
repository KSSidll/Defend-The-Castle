#include "Button.hpp"

Button::Button( SDL_Rect rect, SDL_Renderer* renderer )
{   
    this->rect.x = rect.x;
    this->rect.y = rect.y;
    this->rect.w = rect.w;
    this->rect.h = rect.h;

    this->renderer = renderer;
}

Button::Button( SDL_Rect rect, SDL_Renderer* renderer, void (*callback)( SummonDungeon* dungeon, rapidjson::Value& json, SDL_Renderer* renderer ) ) : Button( rect, renderer )
{
    this->callback = callback;
}

void Button::Render()
{
    switch ( BUTTON_STATE )
    {
    case MOUSE_OUT:
        SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0x00 );
        break;

    case MOUSE_OVER:
        SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0xFF, 0x00 );
        break;

    case MOUSE_DOWN:
        SDL_SetRenderDrawColor( renderer, 0x00, 0xFF, 0x00, 0x00 );
        break;

    case MOUSE_UP:
        SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0x00 );
        break;
    }
    SDL_RenderDrawRect( renderer,&rect );
    SDL_RenderFillRect( renderer, &rect );
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