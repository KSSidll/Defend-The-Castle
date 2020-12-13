#pragma once
#include "Button.hpp"
#include <deque>

class Button;
class Game;

class DifficultySelectionMenu
{
    private:
        Game* game;
        std::deque<Button*> buttons;
        SDL_Renderer* renderer;
        SceneObject* background;
        UILabel* label;

        SDL_Rect easyButtonPos = {412,200,200,100};
        SDL_Rect mediumButtonPos = {412,400,200,100};
        SDL_Rect hardButtonPos = {412,600,200,100};
        
    public:
        DifficultySelectionMenu( SDL_Renderer* renderer, Game* game, TextureManager* textureManager );
        ~DifficultySelectionMenu(){};

        void Render();
        void HandleEvents( SDL_Event* event );
};