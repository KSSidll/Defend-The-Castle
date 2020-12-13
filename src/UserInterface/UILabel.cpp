#include "UILabel.hpp"

UILabel::UILabel( SDL_Renderer* renderer, int xPos, int yPos, const char* fontPath, int fontSize, std::string text, SDL_Color color )
{
    this->renderer = renderer;
    this->position.x = xPos;
    this->position.y = yPos;
    this->color = color;
    this->font = font;
    this->fontSize = fontSize;
    this->text = text;

    this->font = TTF_OpenFont( fontPath, fontSize );

    TTF_SizeText( font, text.c_str(), &position.w, &position.h );

    SDL_Surface* surfaceText = TTF_RenderText_Blended_Wrapped( font, text.c_str(), color, position.w );
    texture = SDL_CreateTextureFromSurface( renderer, surfaceText );
    SDL_FreeSurface( surfaceText );

    SDL_QueryTexture( texture, NULL, NULL, &position.w, &position.h );
}

UILabel::UILabel( SDL_Renderer* renderer, int xPos, int yPos, const char* fontPath, int fontSize, std::string text, SDL_Color color, int labelWidth ) : UILabel ( renderer, xPos, yPos, fontPath, fontSize, text, color )
{
    if( labelWidth > 0 )
    {
        position.x += ( labelWidth - position.w ) / 2;
        wCentered = true;
    }
}

UILabel::UILabel( SDL_Renderer* renderer, int xPos, int yPos, const char* fontPath, int fontSize, std::string text, SDL_Color color, int labelWidth, int labelHeight ) : UILabel ( renderer, xPos, yPos, fontPath, fontSize, text, color, labelWidth )
{
    if( labelHeight > 0 )
    {
        position.y += ( labelHeight - position.h ) / 2;
        hCentered = true;
    }
}

void UILabel::ChangeText( std::string text )
{
    int wRef = position.w;
    int hRef = position.h;

    TTF_SizeText( font, text.c_str(), &position.w, &position.h );

    SDL_Surface* surfaceText = TTF_RenderText_Blended_Wrapped( font, text.c_str(), color, position.w );
    texture = SDL_CreateTextureFromSurface( renderer, surfaceText );
    SDL_FreeSurface( surfaceText );

    SDL_QueryTexture( texture, NULL, NULL, &position.w, &position.h );

    if( wCentered )
    {
        if( position.w < wRef )
            position.x -= (position.w - wRef) / 2;
        else
            position.x += (position.w - wRef) / 2;
    }
    
    if( hCentered )
    {
        if( position.h < hRef )
            position.y -= (position.h - hRef) / 2;
        else
            position.y += (position.h - hRef) / 2;
    }
}

void UILabel::Render()
{
    SDL_RenderCopy( renderer, texture, NULL, &position );
}