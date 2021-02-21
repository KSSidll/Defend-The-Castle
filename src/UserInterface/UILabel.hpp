#pragma once
#include "../Managers/TextureManager.hpp"

class UILabel
{
private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Texture* texture;

    SDL_Rect position;
    SDL_Color color;
    int fontSize;
    bool wCentered = false;
    bool hCentered = false;
    std::string text;


public:
    UILabel();
    ~UILabel();

    UILabel( SDL_Renderer* renderer, int xPos, int yPos, const char* fontPath, int fontSize, std::string text, SDL_Color color );
    UILabel( SDL_Renderer* renderer, int xPos, int yPos, const char* fontPath, int fontSize, std::string text, SDL_Color color, int labelWidth );
    UILabel( SDL_Renderer* renderer, int xPos, int yPos, const char* fontPath, int fontSize, std::string text, SDL_Color color, int labelWidth, int labelHeight );

    void ChangeText( const char* text );
    void Render();

    SDL_Rect GetPosition(){ return position; };
};