#pragma once
#include "../Managers/TextureManager.hpp"

class UILabel
{
private:
    SDL_Renderer* renderer;
    SDL_Rect position;
    SDL_Color color;
    TTF_Font* font;
    int fontSize;
    bool centered;
    std::string text;

    SDL_Texture* texture;

public:
    UILabel( SDL_Renderer* renderer, int xPos, int yPos, const char* fontPath, int fontSize, std::string text, SDL_Color color );
    UILabel( SDL_Renderer* renderer, int xPos, int yPos, const char* fontPath, int fontSize, std::string text, SDL_Color color, int labelWidth );
    UILabel( SDL_Renderer* renderer, int xPos, int yPos, const char* fontPath, int fontSize, std::string text, SDL_Color color, int labelWidth, int labelHeight );
    ~UILabel(){};

    void ChangeText( std::string text );
    void Render();

    SDL_Rect GetPosition(){ return position; };
};