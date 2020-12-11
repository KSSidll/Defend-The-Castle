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
    this->centered = centered;

    this->font = TTF_OpenFont( fontPath, fontSize );

    TTF_SizeText( font, text.c_str(), &position.w, &position.h );

    SDL_Surface* surfaceText = TTF_RenderText_Blended_Wrapped( font, text.c_str(), color, position.w );
    texture = SDL_CreateTextureFromSurface( renderer, surfaceText );
    SDL_FreeSurface( surfaceText );

    SDL_QueryTexture( texture, NULL, NULL, &position.w, &position.h );
}

UILabel::UILabel( SDL_Renderer* renderer, int xPos, int yPos, const char* fontPath, int fontSize, std::string text, SDL_Color color, int labelWidth ) : UILabel ( renderer, xPos, yPos, fontPath, fontSize, text, color )
{
    position.x += ( labelWidth - position.w ) / 2;
}

UILabel::UILabel( SDL_Renderer* renderer, int xPos, int yPos, const char* fontPath, int fontSize, std::string text, SDL_Color color, int labelWidth, int labelHeight ) : UILabel ( renderer, xPos, yPos, fontPath, fontSize, text, color, labelWidth )
{
    position.y += ( labelHeight - position.h ) / 2;
}

void UILabel::ChangeText( std::string text )
{
    TTF_SizeText( font, text.c_str(), &position.w, &position.h );

    SDL_Surface* surfaceText = TTF_RenderText_Blended_Wrapped( font, text.c_str(), color, position.w );
    texture = SDL_CreateTextureFromSurface( renderer, surfaceText );
    SDL_FreeSurface( surfaceText );

    SDL_QueryTexture( texture, NULL, NULL, &position.w, &position.h );
}

void UILabel::Render()
{
    SDL_RenderCopy( renderer, texture, NULL, &position );
}